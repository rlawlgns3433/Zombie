#include "pch.h"
#include "SceneGame.h"
#include "Player.h" 
#include "TextGo.h";
#include "TileMap.h"


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
    AddGameObject(new Tilemap("Background"));

    player = new Player("Player");
    AddGameObject(player);

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

    Tilemap* tilemap = dynamic_cast<Tilemap*>(FindGameObject("Background"));
    tilemap->SetPosition({ windowX * 0.5f, windowY * 0.5f});

    player->SetPosition({ windowX * 0.5f, windowY * 0.5f });
}

void SceneGame::Exit()
{
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
}

void SceneGame::UpdateGameover(float dt)
{

}

void SceneGame::UpdatePause(float dt)
{

}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::SetStatus(GameStatus newStatus)
{
    GameStatus prevStatus = status;

    status = newStatus;

    switch (status)
    {
    case GameStatus::Awake:
        FRAMEWORK.SetTimeScale(0.f);
        break;
    case GameStatus::Game:
        FRAMEWORK.SetTimeScale(1.f);
        break;
    case GameStatus::GameOver:
        FRAMEWORK.SetTimeScale(0.f);
        break;
    case GameStatus::Pause:
        FRAMEWORK.SetTimeScale(0.f);
        break;
    }
}
