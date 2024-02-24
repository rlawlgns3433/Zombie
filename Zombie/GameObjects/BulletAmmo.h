#pragma once
#include "pch.h"
#include "Item.h"
#include "CrossHair.h"
#include "Gun.h"

// 픽업 아이템
class BulletAmmo : public Item
{
protected :
	BulletAmmo(const BulletAmmo&)				= delete;
	BulletAmmo(BulletAmmo&&)					= delete;
	BulletAmmo& operator=(const BulletAmmo&)	= delete;
	BulletAmmo& operator=(BulletAmmo&&)			= delete;

	Gun* gun = nullptr;

public :
	static unsigned amount; // Gun Class 필요 Gun의 Fire() 호출 시 Bullet 생성
	static BulletAmmo* Create(ItemType BulletType = ItemType::None);
	
	BulletAmmo(const std::string& name = "");
	~BulletAmmo() override						= default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

