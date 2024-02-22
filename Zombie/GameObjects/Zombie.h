#pragma once
#include "SpriteGo.h"
#include "Player.h"

class Player;

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

	Player* player;
	Types type = Types::None;

	sf::Vector2f look = { 1.f, 0.f };
	float speed;

	float time = 0.f;

public :
	int maxHp = 100;

	Zombie(const std::string& name = "");
	~Zombie() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};