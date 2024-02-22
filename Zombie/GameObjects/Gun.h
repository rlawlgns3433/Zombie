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
	unsigned gunCapacity;		// ÀüÃ¼ ÃÑ¾Ë ¼ö 
	unsigned gunAmmo;			// ÇÑ ÅºÃ¢
	unsigned currentAmmo;
	float gunDelay;

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

