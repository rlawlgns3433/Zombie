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

	if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
	{
		SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(this);

		player->AddHp(amount * 4);
		if (player->GetHp() > player->GetMaxHp())
		{
			player->SetHp(player->GetMaxHp());
		}
		healthBar->SetRectSize({ player->GetHp(), healthBar->GetCurrentRectSize().y});

		sound.resetBuffer();
		sound.setBuffer(*SOUND_MANAGER.GetResource("sound/pickup.wav"));
		sound.play();
	}
}

void HealthBox::Draw(sf::RenderWindow& window)
{
	Item::Draw(window);
}