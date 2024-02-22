#include "pch.h"
#include "Item.h"
#include "BulletAmmo.h"

unsigned BulletAmmo::amount = 30;
// 픽업 아이템
BulletAmmo* BulletAmmo::Create(ItemType BulletType)
{
	BulletAmmo* bulletAmmo = new BulletAmmo("ammoItem");
	bulletAmmo->textureId = "graphics/ammo_pickup.png";
	bulletAmmo->type = BulletType;
	bulletAmmo->amount = 30;

	return bulletAmmo;
}

BulletAmmo::BulletAmmo(const std::string& name)
	: Item(name)
{
}

void BulletAmmo::Init()
{
	Item::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);

	player = dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("player"));
	gun = dynamic_cast<Gun*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("gun"));
}

void BulletAmmo::Release()
{
	Item::Release();
	delete this;
}

void BulletAmmo::Reset()
{
	Item::Reset();
}

void BulletAmmo::Update(float dt)
{
	Item::Update(dt);
	if (Utils::MyMath::Distance(position, player->GetPosition()) < 50.f)
	{
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(this);
		gun->gunCapacity += amount;
	}
}

void BulletAmmo::Draw(sf::RenderWindow& window)
{
	Item::Draw(window);
}