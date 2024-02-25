#include "pch.h"
#include "SceneTitle.h"
#include "ResourceManager.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Framework.h"


SceneTitle::SceneTitle(SceneIDs id)
	: Scene(id)
{
	windowX = FRAMEWORK.GetWindowSize().x;
	windowY = FRAMEWORK.GetWindowSize().y;
}

void SceneTitle::Init()
{
	spriteGoBackground = new SpriteGo("background");
	spriteGoBackground->SetTexture("graphics/background.png");
	AddGameObject(spriteGoBackground);

	textIntro = new TextGo("intro");
	textIntro->SetFont("fonts/zombiecontrol.ttf");
	textIntro->SetText("PRESS ENTER TO PLAY");
	textIntro->SetTextSize(70);
	textIntro->SetScale({ 1.f, 1.5f });
	textIntro->SetOrigin(Origins::MC);
	textIntro->SetPosition(ScreenToUi({ (int)(windowX * 0.5f), (int)(windowY * 0.8f) }));
	AddGameObject(textIntro, Layers::Ui);

	textHighScore = new TextGo("highscore");
	textHighScore->SetFont("fonts/zombiecontrol.ttf");
	textHighScore->SetText("HI SCORE : " + std::to_string(100)); // 파일 입출력으로 가져오기
	textHighScore->SetTextSize(30);
	textHighScore->SetScale({ 1.f, 1.5f });
	textHighScore->SetOrigin(Origins::TC);
	textHighScore->SetPosition(ScreenToUi({ (int)(windowX * 0.7f), 0 }));

	AddGameObject(textHighScore, Layers::Ui);

	Scene::Init();
}

void SceneTitle::Release()
{
	Scene::Release();

	textIntro = nullptr;
}

void SceneTitle::Reset()
{
}

void SceneTitle::Enter()
{
	Scene::Enter();

}

void SceneTitle::Exit()
{
	Scene::Exit();

	FRAMEWORK.SetTimeScale(1.f);
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	time += dt;

	BlinkIntro(0.5f);

	if (InputManager::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MANAGER.ChangeScene(SceneIDs::SceneSkillUp);
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
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
