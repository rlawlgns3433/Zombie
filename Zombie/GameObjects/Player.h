#pragma once
#include "SpriteGo.h"

class Player : public SpriteGo
{
protected :
	Player(const Player&)				= delete;
	Player(Player&&)					= delete;
	Player& operator=(const Player&)	= delete;
	Player& operator=(Player&&)			= delete;

	sf::Vector2f direction = { 0.f ,0.f };
	sf::Vector2f look = { 1.f, 0.f };
	float speed = 1000;
	bool isMoving = false;

	std::string textureId = "graphics/player.png";

public :Player(const std::string & name = "");
	~Player() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};