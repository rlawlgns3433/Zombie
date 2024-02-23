#include "pch.h"
#include "Zombie.h"
#include "SceneGame.h"

int Zombie::zombieCnt;

Zombie* Zombie::Create(Types zombieType)
{
	if (zombieCnt < 10)
	{
		Zombie* zombie = new Zombie("zombie" + std::to_string(zombieCnt++));
		zombie->type = zombieType;

		switch (zombieType)
		{
		case Zombie::Types::Bloater:
			zombie->textureId = "graphics/bloater.png";
			zombie->maxHp = 40;
			zombie->speed = 100;
			break;
		case Zombie::Types::Chaser:
			zombie->textureId = "graphics/chaser.png";
			zombie->maxHp = 70;
			zombie->speed = 75;
			break;
		case Zombie::Types::Crawler:
			zombie->textureId = "graphics/crawler.png";
			zombie->maxHp = 20;
			zombie->speed = 50;
			break;
		}

		dynamic_cast<SceneGame*>(SCENE_MANAGER.GetCurrentScene())->LoadZombieList(zombie);

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
	
}

void Zombie::Update(float dt)
{
	SpriteGo::Update(dt);



	int bulletSize = SCENE_MANAGER.GetCurrentScene()->FindAll("bullet", bullets, Layers::World);

	if (maxHp > 0)
	{
		sf::Vector2f look = player->GetPosition() - position;
		Utils::MyMath::Normalize(look);

		SetRotation(Utils::MyMath::Angle(look));

		sf::Vector2f pos = position + look * speed * dt;
		if (tilemap != nullptr)
		{
			sf::FloatRect tilemapBounds = tilemap->GetGlobalBounds();
			const sf::Vector2f tileSize = tilemap->GetCellSize();
			tilemapBounds.left += tileSize.x;
			tilemapBounds.top += tileSize.y;
			tilemapBounds.width -= tileSize.x * 2.f;
			tilemapBounds.height -= tileSize.y * 2.f;

			pos.x = Utils::MyMath::Clamp(pos.x, tilemapBounds.left, tilemapBounds.left + tilemapBounds.width);
			pos.y = Utils::MyMath::Clamp(pos.y, tilemapBounds.top, tilemapBounds.top + tilemapBounds.height);
		}

		SetPosition(pos);

		for (auto& b : bullets)
		{
			if (Utils::MyMath::Distance(position, dynamic_cast<Bullet*>(b)->GetPosition()) < 20.f)
			{
				SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(b);

				maxHp -= dynamic_cast<Bullet*>(b)->GetDamage();

				if (maxHp <= 0)
				{
					dynamic_cast<SceneGame*>(SCENE_MANAGER.GetCurrentScene())->LoadZombieList(this);
					speed = 0;
					SetTexture("graphics/blood.png");
					SetSortLayer(-1);
					SCENE_MANAGER.GetCurrentScene()->ResortGameObject(this);
				}
				return;
			}
		}
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}