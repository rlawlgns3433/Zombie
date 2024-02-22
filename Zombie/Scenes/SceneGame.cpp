#include "pch.h"
#include "SceneGame.h"
#include "Player.h" 
#include "TextGo.h";
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "CrossHair.h"
#include "ItemSpawner.h"

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
        spawner->SetPosition(Utils::Random::RandomOnUnitCircle() * 200.f);
        AddGameObject(spawner);
    }

    AddGameObject(new CrossHair("crosshair"), Layers::Ui);

    player = new Player("player");
    AddGameObject(player);

    Tilemap* tilemap = new Tilemap("Background");
    tilemap->sortLayer = -1.f;
    AddGameObject(tilemap);

    Scene::Init(); // 모든 게임 오브젝트 Init()
}

void SceneGame::Release()
{
    Scene::Release();
}

void SceneGame::Reset()
{
}

void SceneGame::Enter()
{
	Scene::Enter();

    worldView.setSize(windowX, windowY);
    worldView.setCenter(0, 0);
    uiView.setSize(windowX, windowY);
    uiView.setCenter(windowX * 0.5f, windowY * 0.5f);

    Tilemap* tilemap = dynamic_cast<Tilemap*>(FindGameObject("Background"));
    tilemap->SetPosition( 0, 0);
    tilemap->SetOrigin(Origins::MC);
    player->SetPosition({ 0, 0 });
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
}

void SceneGame::UpdateGame(float dt)
{
    worldView.setCenter(player->GetPosition());

    if (InputManager::GetKeyDown(sf::Keyboard::Escape))
    {
        status = GameStatus::Pause;
    }
}

void SceneGame::UpdateGameover(float dt)
{

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

