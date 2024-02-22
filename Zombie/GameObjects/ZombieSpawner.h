#pragma once
#include "GameObject.h"
#include "Zombie.h"

class ZombieSpawner : public GameObject
{
protected :
	ZombieSpawner(const ZombieSpawner&)			   = delete;
	ZombieSpawner(ZombieSpawner&&)				   = delete;
	ZombieSpawner& operator=(const ZombieSpawner&) = delete;
	ZombieSpawner& operator=(ZombieSpawner&&)	   = delete;

	std::vector<Zombie::Types> zombieTypes;

	float timer = 0.f;

	float interval = 1.f;
	float intervalMin;
	float intervalMax;

	int spawnCount = 1.f;
	int spawnCountMin;
	int spawnCountMax;

	float radius = 250.f;			// 생성 반경

public :
	ZombieSpawner(const std::string& name = "");
	~ZombieSpawner() override					   = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;

};