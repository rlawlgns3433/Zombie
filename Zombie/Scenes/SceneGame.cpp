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
#include "Gun.h"

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

    tilemap = new Tilemap("background");
    tilemap->SetSortLayer(-1);
    AddGameObject(tilemap);

    InitUI();

    Scene::Init();
}

void SceneGame::InitUI()
{
    textScore = new TextGo("score");
    textScore->Set(*FONT_MANAGER.GetResource("fonts/zombiecontrol.ttf"), "SCORE:", 30, sf::Color::White);
    textScore->SetScale({ 1.f, 1.5f });
    textScore->SetPosition((sf::Vector2f)(WorldToScreen(ScreenToUi({ (int)(windowX * 0.05f), (int)(windowY * 0.f) }))));
    AddGameObject(textScore, Layers::Ui);

    textHighScore = new TextGo("hiscore");
    textHighScore->Set(*FONT_MANAGER.GetResource("fonts/zombiecontrol.ttf"), "HI SCORE:", 30, sf::Color::White);
    textHighScore->SetScale({ 1.f, 1.5f });
    textHighScore->SetPosition((sf::Vector2f)(WorldToScreen(ScreenToUi({ (int)(windowX * 0.7f), (int)(windowY * 0.f) }))));
    AddGameObject(textHighScore, Layers::Ui);

    textAmmos = new TextGo("ammos");
    textAmmos->Set(*FONT_MANAGER.GetResource("fonts/zombiecontrol.ttf"), "6/100", 30, sf::Color::White);
    textAmmos->SetScale({ 1.f, 1.5f });
    textAmmos->SetPosition((sf::Vector2f)(WorldToScreen(ScreenToUi({ (int)(windowX * 0.1f), (int)(windowY * 0.95f) }))));
    textAmmos->SetOrigin(Origins::BL);
    AddGameObject(textAmmos, Layers::Ui);

    textWave = new TextGo("wave");
    textWave->Set(*FONT_MANAGER.GetResource("fonts/zombiecontrol.ttf"), "WAVE:", 30, sf::Color::White);
    textWave->SetScale({ 1.f, 1.5f });
    textWave->SetPosition(1300, 1000);
    textWave->SetPosition((sf::Vector2f)(WorldToScreen(ScreenToUi({ (int)(windowX * 0.7f), (int)(windowY * 0.95f) }))));
    textWave->SetOrigin(Origins::BL);
    AddGameObject(textWave, Layers::Ui);

    textZombieCount = new TextGo("wave");
    textZombieCount->Set(*FONT_MANAGER.GetResource("fonts/zombiecontrol.ttf"), "ZOMBIES:", 30, sf::Color::White);
    textZombieCount->SetScale({ 1.f, 1.5f });
    textZombieCount->SetPosition((sf::Vector2f)(WorldToScreen(ScreenToUi({ (int)(windowX * 0.85f), (int)(windowY * 0.95f) }))));
    textZombieCount->SetOrigin(Origins::BL);
    AddGameObject(textZombieCount, Layers::Ui);

    textGameover = new TextGo("gameover");
    textGameover->Set(*FONT_MANAGER.GetResource("fonts/zombiecontrol.ttf"), "GameOver~ Try Again ^^", 60, sf::Color::White);
    textGameover->SetScale({ 1.f, 1.5f });
    textGameover->SetPosition((sf::Vector2f)(WorldToScreen(ScreenToUi({ (int)(windowX * 0.5f), (int)(windowY * 0.5f) }))));
    textGameover->SetOrigin(Origins::MC);
    textGameover->SetActive(false);
    AddGameObject(textGameover, Layers::Ui);
}

void SceneGame::Release()
{
    Scene::Release();
}

void SceneGame::Reset()
{
    for (GameObject* obj : zombieList)
    {
        RemoveGameObject(obj);
    }
    zombieList.clear();

    for (GameObject* obj : gameObjects)
    {
        if (obj->GetName() == "healthbox" || obj->GetName() == "ammoItem")
        {
            RemoveGameObject(obj);
        }
    }

    SetDeadZombieCount(0);
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
    player->SetHp(player->GetMaxHp());
    deadZombieCount = 0;
    gun = dynamic_cast<Gun*>(FindGameObject("gun"));
}

void SceneGame::Exit()
{
    Scene::Exit();
	FRAMEWORK.SetTimeScale(1.f);

    Reset();
}

void SceneGame::Update(float dt)
{

    Scene::Update(dt);
    UpdateUI(dt);          
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

void SceneGame::UpdateUI(float dt)
{
    textScore->SetText("SCORE : " + std::to_string(score));

    highScore = score > highScore ? score : highScore;
    textHighScore->SetText("HI SCORE : " + std::to_string(highScore));

    textAmmos->SetText(std::to_string(gun->GetCurrentGunAmmo()) + "/" + std::to_string(gun->GetCurrentGunCapacity()));
    textWave->SetText("WAVE : " + std::to_string(wave));
    textZombieCount->SetText("ZOMBIE : " + std::to_string(GetZombieCount() - GetDeadZombieCount()));

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
    FindAll("zombie", zombieList, Layers::World);

    worldView.setCenter(player->GetPosition());

    if (InputManager::GetKeyDown(sf::Keyboard::Escape))
    {
        status = GameStatus::Pause;
    }

    if (player->GetHp() <= 0)
    {
        status = GameStatus::GameOver;
    }

    if (zombieList.size() != 0 &&  GetZombieCount() - GetDeadZombieCount() <= 0 && zombieList.size() == wave * 5)
    {
        // 다음 웨이브 시작
        Reset();
        wave++;
        tilemap->Set({ wave * 15, wave * 15 }, { 50, 50 });
        tilemap->SetSortLayer(-1);
        ResortGameObject(tilemap);

        for (ZombieSpawner* spawner : zombieSpawners)
        {
            spawner->Reset();
        }

        SCENE_MANAGER.ChangeScene(SceneIDs::SceneSkillUp);
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

sf::Vector2f SceneGame::ClampByTilemap(const sf::Vector2f& point)
{
    sf::FloatRect rect = tilemap->GetGlobalBounds();
    rect = Utils::MyMath::ResizeRect(rect, tilemap->GetCellSize() * -2.f);
    return Utils::MyMath::Clamp(point, rect);
}

bool SceneGame::IsInTilemap(const sf::Vector2f& point)
{
    sf::FloatRect rect = tilemap->GetGlobalBounds();
    rect = Utils::MyMath::ResizeRect(rect, tilemap->GetCellSize() * -2.f);

    return rect.contains(point);
}
