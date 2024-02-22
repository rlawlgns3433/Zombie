#include "pch.h"
#include "Item.h"

Item::Item(const std::string& name)
	: SpriteGo(name)
{
}

void Item::Init()
{
	SpriteGo::Init();

	player = dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("player"));
}

void Item::Release()
{
	SpriteGo::Release();
}

void Item::Reset()
{
	SpriteGo::Reset();
}

void Item::Update(float dt)
{
	SpriteGo::Update(dt);

	//if (Utils::MyMath::Distance(position, player->GetPosition()) < 20.f)
	//{
	//}
}

void Item::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
