#include "pch.h"
#include "ItemSpawner.h"

ItemSpawner::ItemSpawner(const std::string& name)
	: GameObject(name)
{
}

void ItemSpawner::Init()
{
	GameObject::Init();
}

void ItemSpawner::Release()
{
	GameObject::Release();
}

void ItemSpawner::Reset()
{
	GameObject::Reset();

	itemTypes.clear();
	itemTypes.push_back(ItemType::None);
	itemTypes.push_back(ItemType::HealthBox);
	itemTypes.push_back(ItemType::HealthBox);
	itemTypes.push_back(ItemType::Bullet);
	itemTypes.push_back(ItemType::Bullet);
	itemTypes.push_back(ItemType::Bullet);

	timer = 0.f;
	interval = 2.f;
	spawnCount = 1;
	radius = 250.f;
}

void ItemSpawner::Update(float dt)
{
	GameObject::Update(dt);

	timer += dt;

	if (timer > interval)
	{
		timer = 0.f;

		for (int i = 0; i < spawnCount; ++i)
		{
			sf::Vector2f itemPosition = position + Utils::Random::RandomInUnitCircle() * radius;
			ItemType itemType = itemTypes[Utils::Random::RandomRange(0, itemTypes.size())];

			if (itemType == ItemType::HealthBox) 
			{
				HealthBox* item = HealthBox::Create(itemType);
				item->Init();
				item->Reset();
				item->SetPosition(itemPosition);

				SCENE_MANAGER.GetCurrentScene()->AddGameObject(item);
			}
			else if (itemType == ItemType::Bullet) 
			{
				BulletAmmo* item = BulletAmmo::Create(itemType); 
				item->Init();
				item->Reset();
				item->SetPosition(itemPosition);

				SCENE_MANAGER.GetCurrentScene()->AddGameObject(item);
			}
		}
	}
}
