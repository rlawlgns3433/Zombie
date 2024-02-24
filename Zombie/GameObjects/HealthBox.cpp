#include "pch.h"
#include "Item.h"
#include "HealthBox.h"
#include "HealthBar.h"

int HealthBox::healthboxCnt;
unsigned HealthBox::amount = 40;

HealthBox* HealthBox::Create(ItemType BulletType)
{
	HealthBox* healthBox = new HealthBox("healthbox");
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
	healthBar = dynamic_cast<HealthBar*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("healthbar"));
}

void HealthBox::Update(float dt)
{
	Item::Update(dt);

	if (Utils::MyMath::Distance(position, player->GetPosition()) < 50.f)
	{
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(this);

		player->hp += amount * 4;
		if (player->hp > player->maxHp)
		{
			player->hp = player->maxHp;
		}
		healthBar->SetRectSize({ player->hp, healthBar->GetCurrentRectSize().y });
	}
}

void HealthBox::Draw(sf::RenderWindow& window)
{
	Item::Draw(window);
}