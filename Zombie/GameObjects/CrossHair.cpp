#include "pch.h"
#include "CrossHair.h"

CrossHair::CrossHair(const std::string& name)
	: SpriteGo(name)
{
}

void CrossHair::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);
}

void CrossHair::Release()
{
	SpriteGo::Release();
}

void CrossHair::Reset()
{
	SpriteGo::Reset();
	SetPosition(InputManager::GetMousePos());
}

void CrossHair::Update(float dt)
{
	SpriteGo::Update(dt);
	SetPosition(InputManager::GetMousePos());
}

void CrossHair::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}