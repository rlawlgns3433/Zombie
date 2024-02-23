#include "pch.h"
#include "SceneGame.h"
#include "Player.h" 
#include "TextGo.h";
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "CrossHair.h"
#include "ItemSpawner.h"
#include "HealthBar.h"

SceneGame::SceneGame(SceneIDs id) 
    : Scene(id)
{
    windowX = FRAMEWORK.GetWindowSize().x;
    windowY = FRAMEWORK.GetWindowSize().y;
}

SceneGame::~SceneGame()
{
    Release();
}

void SceneGame::Init()
{
    zombieSpawners.push_back(new ZombieSpawner("zombieSpawner1"));
    zombieSpawners.push_back(new ZombieSpawner("zombieSpawner2"));

    for (auto spawner : zombieSpawners) 
    {
        spawner->SetPosition(Utils::Random::RandomOnUnitCircle() * 250.f);
        AddGameObject(spawner);
    }

    itemSpawners.push_back(new ItemSpawner("itemspawner"));

    for (auto spawner : itemSpawners)
    {
        spawner->SetPosition(Utils::Random::RandomInUnitCircle());
        AddGameObject(spawner);
    }

    AddGameObject(new CrossHair("crosshair"), Layers::Ui);

    player = new Player("player");
    AddGameObject(player);

    Tilemap* tilemap = new Tilemap("background");
    tilemap->sortLayer = -1.f;
    AddGameObject(tilemap);


    textScore = new TextGo("score");
    textScore->Set(*FONT_MANAGER.GetResource("fonts/zombiecontrol.ttf"), "SCORE:", 30, sf::Color::White);
    textScore->SetScale({ 1.f, 1.5f });
    textScore->SetPosition(0, 0);
    AddGameObject(textScore, Layers::Ui);

    textHighScore = new TextGo("hiscore");
    textHighScore->Set(*FONT_MANAGER.GetResource("fonts/zombiecontrol.ttf"), "HI SCORE:", 30, sf::Color::White);
    textHighScore->SetScale({ 1.f, 1.5f });
    textHighScore->SetPosition(500, 0);
    AddGameObject(textHighScore, Layers::Ui);
    
    textAmmos = new TextGo("ammos");
    textAmmos->Set(*FONT_MANAGER.GetResource("fonts/zombiecontrol.ttf"), "6/100", 30, sf::Color::White);
    textAmmos->SetScale({ 1.f, 1.5f });
    textAmmos->SetPosition(100, 1000);
    textAmmos->SetOrigin(Origins::BL);
    AddGameObject(textAmmos, Layers::Ui);

    textWave = new TextGo("wave");
    textWave->Set(*FONT_MANAGER.GetResource("fonts/zombiecontrol.ttf"), "WAVE:", 30, sf::Color::White);
    textWave->SetScale({ 1.f, 1.5f });
    textWave->SetPosition(1300, 1000);
    textAmmos->SetOrigin(Origins::BL);
    AddGameObject(textWave, Layers::Ui);

    textZombieCount = new TextGo("wave");
    textZombieCount->Set(*FONT_MANAGER.GetResource("fonts/zombiecontrol.ttf"), "ZOMBIES:", 30, sf::Color::White);
    textZombieCount->SetScale({ 1.f, 1.5f });
    textZombieCount->SetPosition(1600, 1000);
    textAmmos->SetOrigin(Origins::BL);
    AddGameObject(textZombieCount, Layers::Ui);

    textGameover = new TextGo("gameover");
    textGameover->Set(*FONT_MANAGER.GetResource("fonts/zombiecontrol.ttf"), "GameOver~ Try Again ^^", 30, sf::Color::White);
    textGameover->SetScale({ 1.f, 1.5f });
    textGameover->SetPosition(windowX * 0.5f, windowY * 0.5f);
    textGameover->SetOrigin(Origins::MC);
    textGameover->SetActive(false);
    AddGameObject(textGameover, Layers::Ui);



    Scene::Init(); // 모든 게임 오브젝트 Init()
}

void SceneGame::Release()
{
    Scene::Release();
}

void SceneGame::Reset()
{
    for (GameObject* obj : deadZombie)
    {
        RemoveGameObject(obj);
    }

    for (GameObject* obj : gameObjects)
    {
        if (obj->GetName() == "healthbox" || obj->GetName() == "ammoItem")
        {
            RemoveGameObject(obj);
        }
    }

    player->hp = player->maxHp;
}

void SceneGame::Enter()
{
	Scene::Enter();

    worldView.setSize(windowX, windowY);
    worldView.setCenter(0, 0);
    uiView.setSize(windowX, windowY);
    uiView.setCenter(windowX * 0.5f, windowY * 0.5f);

    Tilemap* tilemap = dynamic_cast<Tilemap*>(FindGameObject("background"));
    tilemap->SetPosition( 0, 0);
    tilemap->SetOrigin(Origins::MC);
    player->SetPosition({ 0, 0 });

    Reset();
}

void SceneGame::Exit()
{
    Scene::Exit();
	FRAMEWORK.SetTimeScale(1.f);
}

void SceneGame::Update(float dt)
{
    Scene::Update(dt);
    SetStatus(status);

    switch (status)
    {
    case GameStatus::Awake:
        UpdateAwake(dt);
        break;
    case GameStatus::Game:
        UpdateGame(dt);
        break;
    case GameStatus::GameOver:
        UpdateGameover(dt);
        break;
    case GameStatus::Pause:
        UpdatePause(dt);
        break;
    default:
        break;
    }
}

void SceneGame::UpdateAwake(float dt)
{
    if (InputManager::GetKeyDown(sf::Keyboard::Enter))
    {
        status = GameStatus::Game;
    }
}

void SceneGame::UpdateGame(float dt)
{
    worldView.setCenter(player->GetPosition());

    if (InputManager::GetKeyDown(sf::Keyboard::Escape))
    {
        status = GameStatus::Pause;
    }

    if (player->hp <= 0)
    {
        status = GameStatus::GameOver;
    }
}

void SceneGame::UpdateGameover(float dt)
{
    textGameover->SetActive(true);

    if (InputManager::GetKeyDown(sf::Keyboard::Escape))
    {
        SCENE_MANAGER.ChangeScene(SceneIDs::SceneTitle);
        status = GameStatus::Awake;
        textGameover->SetActive(false);
    }
}

void SceneGame::UpdatePause(float dt)
{
    if (InputManager::GetKeyDown(sf::Keyboard::Escape))
    {
        status = GameStatus::Game;
    }
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::LoadZombieList(Zombie* zombie)
{
    if (std::find(deadZombie.begin(), deadZombie.end(), zombie) == deadZombie.end())
    {
        deadZombie.push_back(zombie);
    }
}
