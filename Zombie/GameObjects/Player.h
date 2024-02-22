#pragma once
#include "SpriteGo.h"
#include "CrossHair.h"
#include "Gun.h"

class Gun;

class Player : public SpriteGo
{
protected :
	Player(const Player&)				= delete;
	Player(Player&&)					= delete;
	Player& operator=(const Player&)	= delete;
	Player& operator=(Player&&)			= delete;

	Gun* gun = nullptr;
	CrossHair* crossHair = nullptr;

	sf::Vector2f direction = { 0.f ,0.f };
	sf::Vector2f look = { 1.f, 0.f };
	
	std::string textureId = "graphics/player.png";

	float speed = 1000;
	bool isMoving = false;



public :
	// protected로 변환 필요
	float maxHp = 400.f;
	float hp = maxHp;
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
};