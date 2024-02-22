#include "pch.h"
#include "Item.h"
#include "HealthBox.h"

int HealthBox::healthboxCnt;

HealthBox* HealthBox::Create(ItemType BulletType)
{
	HealthBox* healthBox = new HealthBox("healthbox" + std::to_string(healthboxCnt));
	healthBox->type = BulletType;
	healthBox->textureId = "graphics/health_pickup.png";
	healthBox->amount = 40.f;

	return healthBox;
}

HealthBox::HealthBox(const std::string& name)
	: Item(name)
{
}

void HealthBox::Init()
{
	Item::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);
}

void HealthBox::Release()
{
	Item::Release();
	delete this;
}

void HealthBox::Reset()
{
	Item::Reset();

	player = dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("player"));
}

void HealthBox::Update(float dt)
{
	Item::Update(dt);

	if (Utils::MyMath::Distance(position, player->GetPosition()) < 50.f)
	{
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(this);

		player->hp += amount;
		if (player->hp > player->maxHp)
		{
			player->hp = player->maxHp;
		}
	}
}

void HealthBox::Draw(sf::RenderWindow& window)
{
	Item::Draw(window);
}