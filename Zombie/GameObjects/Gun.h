#pragma once
#include "GameObject.h"
#include "Bullet.h"

class Gun : public GameObject
{
protected:
	Gun(const Gun&)				= delete;
	Gun(Gun&&)					= delete;
	Gun& operator=(const Gun&)  = delete;
	Gun& operator=(Gun&&)		= delete;

	float time = 0.f;
	bool availShoot = true;

public:
	static int gunCount;

	unsigned gunCapacity = 6;	// ÀüÃ¼ ÃÑ¾Ë ¼ö 
	unsigned currentGunCapacity = 6;
	unsigned gunAmmo = 6;		// ÇÑ ÅºÃ¢
	unsigned currentAmmo = 6; // ³» ÇöÀç ÅºÃ¢


	float gunDelay = 2.f;
	float reloadDelay = 0.8f;
	bool isReload = false;

	Gun(const std::string& name = "");
	~Gun() override				= default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Fire();
	void Reload();
};