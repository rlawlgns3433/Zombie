#include "pch.h"
#include "Player.h"

Player::Player(const std::string& name)
	: SpriteGo(name)
{
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);

}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2f mousePosition = InputManager::GetMousePos();
	sf::Vector2f mouseWorldPosition = mousePosition; // 변환 필요

	look = mouseWorldPosition - position;
	Utils::Normalize(look);

	float angle = Utils::Angle(look);
	sprite.setRotation(angle);

	direction.x = InputManager::GetAxis(Axis::Horizontal);
	direction.y = InputManager::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(direction) > 1.f) // 대각 이동 시 속도가 1.414 배 빠르기 때문에 정규화한다.
	{
		Utils::Normalize(direction);
	}

	Translate(direction * speed * dt);

}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
