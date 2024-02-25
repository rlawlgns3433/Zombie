#pragma once
#include "Scene.h"

class Player;
class ZombieSpawner;
class ItemSpawner;
class Zombie;
class TextGo;
class HealthBar;
class Tilemap;
class Gun;

class SceneGame : public Scene
{
protected:
	GameStatus status = GameStatus::Game;

	std::vector<ZombieSpawner*> zombieSpawners;
	std::vector<ItemSpawner*> itemSpawners;
	std::list<Zombie*> deadZombie;

	std::list<GameObject*> zombieList;

	Tilemap* tilemap = nullptr;

	Player* player = nullptr;
	Gun* gun = nullptr;
	TextGo* textScore = nullptr;
	TextGo* textHighScore = nullptr;
	TextGo* textAmmos = nullptr;
	TextGo* textWave = nullptr;
	TextGo* textZombieCount = nullptr;
	TextGo* textGameover = nullptr;

	HealthBar* healthBar = nullptr;

	float windowX = 0.f;
	float windowY = 0.f;
	int wave = 1;

	int score = 0;
	int highScore = 0;

	int deadZombieCount = 0;

public:
	SceneGame(SceneIDs id);
	virtual ~SceneGame();

	SceneGame(const SceneGame&) = delete;
	SceneGame(SceneGame&&) = delete;
	SceneGame& operator=(const SceneGame&) = delete;
	SceneGame& operator=(SceneGame&&) = delete;

	// SceneDev1을(를) 통해 상속됨 
	void Init() override;
	void InitUI();
	void Release() override;
	void Reset();
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void UpdateUI(float dt);
	void UpdateAwake(float dt);
	void UpdateGame(float dt);
	void UpdateGameover(float dt);
	void UpdatePause(float dt);
	void Draw(sf::RenderWindow& window);

	int GetScore() const { return this->score; }
	void SetScore(int score) { this->score = score; }
	void AddScore(int score) { this->score += score; }

	int GetZombieCount() const { return zombieList.size(); }

	int GetWave() const { return this->wave; }
	void SetWave(int wave) { this->wave = wave; }

	int GetDeadZombieCount() { return this->deadZombieCount; }
	void SetDeadZombieCount(int count) { this->deadZombieCount = count; }

	void LoadZombieList(Zombie* zombie);
	sf::Vector2f ClampByTilemap(const sf::Vector2f& point);
	bool IsInTilemap(const sf::Vector2f& point);
	const std::list<GameObject*>& GetZombieList() const { return zombieList; }
};