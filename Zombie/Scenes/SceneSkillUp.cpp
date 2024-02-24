#include "pch.h"
#include "SceneSkillUp.h"
#include "SpriteGo.h"
#include "TextGo.h";
#include "Gun.h"
#include "Player.h"
#include "HealthBox.h"
#include "BulletAmmo.h"

SceneSkillUp::SceneSkillUp(SceneIDs id)
	: Scene(id)
{
	windowX = FRAMEWORK.GetWindowSize().x;
	windowY = FRAMEWORK.GetWindowSize().y;
}

void SceneSkillUp::Init()
{
	for (int i = 0; i < 6; ++i)
	{
		text = new TextGo("skilluptext" + std::to_string(i));
		text->SetFont("fonts/zombiecontrol.ttf");
		text->SetText(skillTextNames[i]);
		text->SetTextSize(40);
		text->SetScale({ 1.f, 1.5f });
		text->SetPosition({ windowX * 0.05f, windowY * 0.3f + 60 * i });
		AddGameObject(text, Layers::Ui);
	}

	spriteGoBackground = new SpriteGo("background");
	spriteGoBackground->SetTexture("graphics/background.png");
	spriteGoBackground->SetSortLayer(-1);
	AddGameObject(spriteGoBackground);


	Scene::Init();
}

void SceneSkillUp::Release()
{
	Scene::Release();
}

void SceneSkillUp::Reset()
{
}

void SceneSkillUp::Enter()
{
	Scene::Enter();

	gun = dynamic_cast<Gun*>(SCENE_MANAGER.GetScene(SceneIDs::SceneGame)->FindGameObject("gun"));
	player = dynamic_cast<Player*>(SCENE_MANAGER.GetScene(SceneIDs::SceneGame)->FindGameObject("player"));
}

void SceneSkillUp::Exit()
{
	Scene::Exit();
}

void SceneSkillUp::Update(float dt)
{
	Scene::Update(dt);
	time += dt;

	if (time > 5.f)
	{
		SCENE_MANAGER.ChangeScene(SceneIDs::SceneGame);
	}

	if (InputManager::GetKeyDown(sf::Keyboard::Num1) || InputManager::GetKeyDown(sf::Keyboard::Numpad1))
	{
		gun->gunDelay -= 0.2f;
		SCENE_MANAGER.ChangeScene(SceneIDs::SceneGame);
	}
	else if (InputManager::GetKeyDown(sf::Keyboard::Num2) || InputManager::GetKeyDown(sf::Keyboard::Numpad2))
	{
		gun->gunAmmo += 6;
		SCENE_MANAGER.ChangeScene(SceneIDs::SceneGame);
	}
	else if (InputManager::GetKeyDown(sf::Keyboard::Num3) || InputManager::GetKeyDown(sf::Keyboard::Numpad3))
	{
		player->maxHp += 40;
		SCENE_MANAGER.ChangeScene(SceneIDs::SceneGame);
	}
	else if (InputManager::GetKeyDown(sf::Keyboard::Num4) || InputManager::GetKeyDown(sf::Keyboard::Numpad4))
	{
		player->AddSpeed(50);
		SCENE_MANAGER.ChangeScene(SceneIDs::SceneGame);
	}
	else if (InputManager::GetKeyDown(sf::Keyboard::Num5) || InputManager::GetKeyDown(sf::Keyboard::Numpad5))
	{
		HealthBox::amount += 10;
		SCENE_MANAGER.ChangeScene(SceneIDs::SceneGame);
	}
	else if (InputManager::GetKeyDown(sf::Keyboard::Num6) || InputManager::GetKeyDown(sf::Keyboard::Numpad6))
	{
		BulletAmmo::amount += 10;
		SCENE_MANAGER.ChangeScene(SceneIDs::SceneGame);
	}
}

void SceneSkillUp::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
