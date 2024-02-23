#pragma once
#include "Scene.h"

class Player;
class ZombieSpawner;
class ItemSpawner;
class Zombie;
class TextGo;
class HealthBar;

class SceneGame : public Scene
{
protected :
	GameStatus status = GameStatus::Game;

	std::vector<ZombieSpawner*> zombieSpawners;
	std::vector<ItemSpawner*> itemSpawners;
	std::list<Zombie*> deadZombie;

	Player* player = nullptr;
	TextGo* textScore = nullptr;
	TextGo* textHighScore = nullptr;
	TextGo* textAmmos = nullptr;
	TextGo* textWave = nullptr;
	TextGo* textZombieCount = nullptr;
	TextGo* textGameover = nullptr;

	HealthBar* healthBar = nullptr;

	float windowX = 0.f;
	float windowY = 0.f;
	unsigned wave = 1;

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

	unsigned GetWave() const { return wave; }
	void LoadZombieList(Zombie* zombie);
};