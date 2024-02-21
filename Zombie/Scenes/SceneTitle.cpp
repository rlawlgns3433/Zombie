#include "pch.h"
#include "SceneTitle.h"
#include "ResourceManager.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Framework.h"


SceneTitle::SceneTitle(SceneIDs id)
	: Scene(id)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{

}

void SceneTitle::Release()
{
	Scene::Release();

	textIntro = nullptr;

}

void SceneTitle::Enter()
{
	Scene::Enter();

}

void SceneTitle::Exit()
{
	FRAMEWORK.SetTimeScale(1.f);
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	time += dt;

	//BlinkIntro(0.7f);

	if (InputManager::GetKeyDown(sf::Keyboard::Enter))
	{
		//SCENEMANAGER.StopBGM();
		//SCENEMANAGER.ChangeScene(SceneIDs::SceneSelectMode);
	}
}


void SceneTitle::BlinkIntro(float blinkTime)
{
	this->blinkTime = blinkTime;

	if (time >= 0 && time < blinkTime)
	{
		textIntro->SetActive(true);
	}
	else if (time >= blinkTime && time < blinkTime * 2)
	{
		textIntro->SetActive(false);
	}
	else if (time >= blinkTime * 2)
	{
		time = 0.f;
	}
}
