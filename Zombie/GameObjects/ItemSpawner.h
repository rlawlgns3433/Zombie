#pragma once
#include "GameObject.h"
#include "HealthBox.h"
#include "BulletAmmo.h"

class ItemSpawner : public GameObject
{
protected :
	ItemSpawner(const ItemSpawner&)			   = delete;
	ItemSpawner(ItemSpawner&&)				   = delete;
	ItemSpawner& operator=(const ItemSpawner&) = delete;
	ItemSpawner& operator=(ItemSpawner&&)	   = delete;

	std::vector<ItemType> itemTypes;
	SceneGame* sceneGame = nullptr;

	float timer = 0.f;

	float interval = 5.f;
	float intervalMin;
	float intervalMax;

	int spawnCount = 1.f;
	int spawnCountMin;
	int spawnCountMax;

	float radius = 250.f;			// 생성 반경
public :
	ItemSpawner(const std::string& name = "");
	~ItemSpawner() override					   = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
};