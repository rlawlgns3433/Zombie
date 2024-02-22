#pragma once
#include "pch.h"
#include "Item.h"
#include "CrossHair.h"
#include "Gun.h"

// �Ⱦ� ������
class BulletAmmo : public Item
{
protected :
	BulletAmmo(const BulletAmmo&)				= delete;
	BulletAmmo(BulletAmmo&&)					= delete;
	BulletAmmo& operator=(const BulletAmmo&)	= delete;
	BulletAmmo& operator=(BulletAmmo&&)			= delete;

	Gun* gun = nullptr;

	//unsigned damage = 20; bullet����
	unsigned amount = 0; // Gun Class �ʿ� Gun�� Fire() ȣ�� �� Bullet ����
	//float speed = 500.f; bullet����

public :
	static BulletAmmo* Create(ItemType BulletType = ItemType::None);
	
	BulletAmmo(const std::string& name = "");
	~BulletAmmo() override						= default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

