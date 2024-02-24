#pragma once
#include "SpriteGo.h"
#include "Player.h"
#include "Tilemap.h"
#include "SceneGame.h"

class Player;
class Tilemap;

class Zombie : public SpriteGo
{
public :
	enum class Types
	{
		None,
		Bloater,
		Chaser,
		Crawler,
		Count,
	};
	static int zombieCnt;
	static const int totalTypes = 3;
	static Zombie* Create(Types zombieType = Types::None);

protected :
	Zombie(const Zombie&)				= delete;
	Zombie(Zombie&&)					= delete;
	Zombie& operator=(const Zombie&)	= delete;
	Zombie& operator=(Zombie&&)			= delete;

	std::list<GameObject*> bullets;

	SceneGame* sceneGame = nullptr;
	Tilemap* tilemap = nullptr;
	Player* player = nullptr;
	Types type = Types::None;

	sf::Vector2f look = { 1.f, 0.f };

	bool isDead = false;

	float speed;
	float attackInterval;
	float attackTimer = 0.f;

	int hp;
	int maxHp = 100;

public :

	int damage = 20;
	Zombie(const std::string& name = "");
	~Zombie() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void OnDamage(int damage);
	void OnDie();

	bool IsDead() { return isDead; };
};