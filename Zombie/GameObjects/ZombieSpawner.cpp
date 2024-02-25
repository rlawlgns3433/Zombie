#include "pch.h"
#include "ZombieSpawner.h"
#include "SceneGame.h"

int ZombieSpawner::zombieCount = 0;

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
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MANAGER.GetCurrentScene());

	zombieTypes.clear();
	zombieTypes.push_back(Zombie::Types::Bloater);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Crawler);
	zombieTypes.push_back(Zombie::Types::Crawler);

	timer = 0.f;
	interval = 1.f;
	spawnCount = 1;
	radius = 250.f * sceneGame->GetWave();
	zombieCount = 0;

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
			Zombie::Types zombieType = zombieTypes[Utils::Random::RandomRange(0, zombieTypes.size() - 1)];

			Zombie* zombie = Zombie::Create(zombieType);
			if (zombie != nullptr && zombieCount < sceneGame->GetWave() * 5)
			{
				zombie->Init();
				zombie->Reset();
				sf::Vector2f zombiePosition = position + Utils::Random::RandomInUnitCircle() * radius;

				if (sceneGame != nullptr)
				{
					zombiePosition = sceneGame->ClampByTilemap(zombiePosition);
				}
				++zombieCount;

				zombie->SetPosition(zombiePosition);
				SCENE_MANAGER.GetCurrentScene()->AddGameObject(zombie);
			}
		}
	}
}
