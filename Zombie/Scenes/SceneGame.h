#pragma once
#include "Scene.h"

class Player;

class SceneGame : public Scene
{
protected :
	GameStatus status = GameStatus::Game;

	Player* player = nullptr;

	float windowX = 0.f;
	float windowY = 0.f;

public :
	SceneGame(SceneIDs id);
	virtual ~SceneGame();

	SceneGame(const SceneGame&)				= delete;
	SceneGame(SceneGame&&)					= delete;
	SceneGame& operator=(const SceneGame&)	= delete;
	SceneGame& operator=(SceneGame&&)		= delete;

	// SceneDev1을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	virtual void Reset();
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void UpdateAwake(float dt);
	void UpdateGame(float dt);
	void UpdateGameover(float dt);
	void UpdatePause(float dt);
	void Draw(sf::RenderWindow& window);

	void SetStatus(GameStatus newStatus);

};