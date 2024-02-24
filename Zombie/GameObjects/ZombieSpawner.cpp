#include "pch.h"
#include "ZombieSpawner.h"
#include "SceneGame.h"

ZombieSpawner::ZombieSpawner(const std::string& name)
	: GameObject(name)
{
}

void ZombieSpawner::Init()
{
	GameObject::Init();
}

void ZombieSpawner::Release()
{
	GameObject::Release();
}

void ZombieSpawner::Reset()
{
	GameObject::Reset();

	zombieTypes.clear();
	zombieTypes.push_back(Zombie::Types::Bloater);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Crawler);
	zombieTypes.push_back(Zombie::Types::Crawler);

	timer = 0.f;
	interval = 1.f;
	spawnCount = 2;
	radius = 250.f;

	sceneGame = dynamic_cast<SceneGame*>(SCENE_MANAGER.GetCurrentScene());
}

void ZombieSpawner::Update(float dt)
{
	GameObject::Update(dt);

	timer += dt;
	if (timer > interval)
	{
		timer = 0.f;

		for (int i = 0; i < spawnCount; ++i)
		{
			Zombie::Types zombieType = zombieTypes[Utils::Random::RandomRange(0, zombieTypes.size())];

			Zombie* zombie = Zombie::Create(zombieType);
			if (zombie != nullptr)
			{
				zombie->Init();
				zombie->Reset();
				sf::Vector2f zombiePosition = position + Utils::Random::RandomInUnitCircle() * radius;

				if (sceneGame != nullptr)
				{
					zombiePosition = sceneGame->ClampByTilemap(zombiePosition);
				}

				zombie->SetPosition(zombiePosition);

				SCENE_MANAGER.GetCurrentScene()->AddGameObject(zombie);
			}
		}
	}
}
