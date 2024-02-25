#pragma once
#include "GameObject.h"
#include "CrossHair.h"
#include "Player.h"
#include "Zombie.h"
#include "SceneGame.h"

class Player;
class Zombie;
class SceneGame;

class Bullet : public GameObject
{
protected :
	Bullet(const Bullet&)				= delete;
	Bullet(Bullet&&)					= delete;
	Bullet& operator=(const Bullet&)	= delete;
	Bullet& operator=(Bullet&&)			= delete;

	SceneGame* sceneGame = nullptr;
	Player* player = nullptr;

	CrossHair* crossHair = nullptr;
	sf::CircleShape shape;

	float speed = 1000.f;
	float damage = 100.f;
	sf::Vector2f direction{ 1.f, 0.f };

public:
	Bullet(const std::string& name = "");
	~Bullet() override					= default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	float GetDamage() const { return damage; }
	sf::FloatRect GetGlobalBounds() override { return shape.getGlobalBounds(); }

	sf::Vector2f GetPosition() const { return shape.getPosition(); }
	void SetDirection(const sf::Vector2f direction) { this->direction = direction; }
};