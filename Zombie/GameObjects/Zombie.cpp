#include "pch.h"
#include "Zombie.h"
#include "SceneGame.h"

int Zombie::zombieCnt;

Zombie* Zombie::Create(Types zombieType)
{
	if (zombieCnt < 10)
	{
		Zombie* zombie = new Zombie("zombie");
		zombie->type = zombieType;

		switch (zombieType)
		{
		case Zombie::Types::Bloater:
			zombie->textureId = "graphics/bloater.png";
			zombie->maxHp = 40;
			zombie->speed = 100;
			zombie->damage = 20;
			zombie->attackInterval = 1.f;
			break;
		case Zombie::Types::Chaser:
			zombie->textureId = "graphics/chaser.png";
			zombie->maxHp = 70;
			zombie->speed = 75;
			zombie->damage = 30;
			zombie->attackInterval = 1.5f;
			break;
		case Zombie::Types::Crawler:
			zombie->textureId = "graphics/crawler.png";
			zombie->maxHp = 20;
			zombie->speed = 50;
			zombie->damage = 15;
			zombie->attackInterval = 0.7f;
			break;
		}

		++zombieCnt;
		return zombie;
	}
	return nullptr;
}

Zombie::Zombie(const std::string& name)
	: SpriteGo(name)
{
}

void Zombie::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);
}

void Zombie::Release()
{
	SpriteGo::Release();
	delete this;
}

void Zombie::Reset()
{
	SpriteGo::Reset();

	player = dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("player"));
	tilemap = dynamic_cast<Tilemap*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("background"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MANAGER.GetCurrentScene());

	isDead = false;
	hp = maxHp;
	attackTimer = attackInterval;
}

void Zombie::Update(float dt)
{
	SpriteGo::Update(dt);

	int bulletSize = SCENE_MANAGER.GetCurrentScene()->FindAll("bullet", bullets, Layers::World);

	if (isDead) return;

	look = player->GetPosition() - position;
	Utils::MyMath::Normalize(look);

	SetRotation(Utils::MyMath::Angle(look));

	sf::Vector2f pos = position + look * speed * dt;
	if (sceneGame != nullptr)
	{
		pos = sceneGame->ClampByTilemap(pos);
	}

	SetPosition(pos);
}

void Zombie::FixedUpdate(float dt)
{
	attackTimer += dt;

	if (attackTimer > attackInterval)
	{
		if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
		{
			player->OnDamage(damage);
			player->SetInvincible(true);
			attackTimer = 0.f;
		}
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Zombie::OnDamage(int damage)
{
	if (isDead) return;

	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;
		OnDie();
	}
}

void Zombie::OnDie()
{
	if (isDead) return;

	isDead = true;
	speed = 0;
	damage = 0;
	SetTexture("graphics/blood.png");
	SetSortLayer(-1);
	SCENE_MANAGER.GetCurrentScene()->ResortGameObject(this);

	//SetActive(false);
	//sceneGame->RemoveGameObject(this); 씬 변경 시 처리
}