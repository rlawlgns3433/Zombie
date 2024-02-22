#pragma once
#include "GameObject.h"
#include "CrossHair.h"
#include "Player.h"
#include "Zombie.h"

class Player;
class Zombie;

class Bullet : public GameObject
{
protected :
	Bullet(const Bullet&)				= delete;
	Bullet(Bullet&&)					= delete;
	Bullet& operator=(const Bullet&)	= delete;
	Bullet& operator=(Bullet&&)			= delete;

	Player* player = nullptr;

	CrossHair* crossHair = nullptr;
	sf::CircleShape shape;

	float speed = 1000.f;
	float damage = 30.f;

public:
	sf::Vector2f direction{ 1.f, 0.f };
	Bullet(const std::string& name = "");
	~Bullet() override					= default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	float GetDamage() const { return damage; }

	sf::Vector2f GetPosition() const { return shape.getPosition(); }

};