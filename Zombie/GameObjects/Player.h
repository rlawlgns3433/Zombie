#pragma once
#include "SpriteGo.h"
#include "CrossHair.h"
#include "Gun.h"
#include "HealthBar.h"
#include "Tilemap.h"

class Gun;
class HealthBar;
class Tilemap;

class Player : public SpriteGo
{
protected :
	Player(const Player&)				= delete;
	Player(Player&&)					= delete;
	Player& operator=(const Player&)	= delete;
	Player& operator=(Player&&)			= delete;

	Tilemap* tilemap = nullptr;

	Gun* gun = nullptr;
	CrossHair* crossHair = nullptr;
	HealthBar* healthBar = nullptr;

	sf::Vector2f direction = { 0.f ,0.f };
	sf::Vector2f look = { 1.f, 0.f };
	
	std::string textureId = "graphics/player.png";

	float speed = 500.f;
	bool isMoving = false;

	int cellCountX;
	int cellCountY;
	int cellSizeX;
	int cellSizeY;

public :
	// protected로 변환 필요
	float maxHp = 400.f;
	float hp = 400.f;
	float damageInterval = 1.f;
	bool nowDamage = false;
	float time = 0.f;

	Player(const std::string & name = "");
	~Player() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetSpeed(float speed) { this->speed = speed; }
	void AddSpeed(float addSpeed) { this->speed += addSpeed; }
};