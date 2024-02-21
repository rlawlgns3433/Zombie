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
	sf::Vector2f mouseWorldPosition = mousePosition; // ��ȯ �ʿ�

	look = mouseWorldPosition - position;
	Utils::Normalize(look);

	float angle = Utils::Angle(look);
	sprite.setRotation(angle);

	direction.x = InputManager::GetAxis(Axis::Horizontal);
	direction.y = InputManager::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(direction) > 1.f) // �밢 �̵� �� �ӵ��� 1.414 �� ������ ������ ����ȭ�Ѵ�.
	{
		Utils::Normalize(direction);
	}

	Translate(direction * speed * dt);

}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
