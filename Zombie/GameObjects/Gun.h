#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "Player.h"

class SceneGame;
class Player;

class Gun : public GameObject
{
protected:
	Gun(const Gun&)				= delete;
	Gun(Gun&&)					= delete;
	Gun& operator=(const Gun&)  = delete;
	Gun& operator=(Gun&&)		= delete;

	SceneGame* sceneGame = nullptr;
	Player* player = nullptr;

	float reloadTimer = 0.f;
	float fireTimer = 0.f;
	bool availShoot = true;

	int currentGunCapacity = 6; // ÀüÃ¼ ÅºÀÇ ¼ö
	int gunAmmo = 6;		// ÇÑ ÅºÃ¢
	int currentGunAmmo = 6; // ³» ÇöÀç ÅºÃ¢

	float gunDelay = 2.f;
	float reloadDelay = 0.8f;

	bool isReload = false;

public:
	Gun(const std::string& name = "");
	~Gun() override				= default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Fire();
	void Reload();


	int GetCurrentGunCapacity() const { return this->currentGunCapacity; }
	void AddCurrentGunCapacity(int add) { this->currentGunCapacity += add; }
	void SetCurrentGunCapacity(int currentGunCapacity) { this->currentGunCapacity = currentGunCapacity; }

	int GetGunAmmo() const { return this->gunAmmo; }
	void AddGunAmmo(int add) { this->gunAmmo += add; }
	void SetGunAmmo(int ammo) { this->gunAmmo = ammo; }

	int GetCurrentGunAmmo() const { return this->currentGunAmmo; }
	void SetCurrentGunAmmo(int ammo) { this->currentGunAmmo = ammo; }

	float GetGunDelay() const { return this->gunDelay; }
	void SetGunDelay(float delay) { this->gunDelay = delay; }
};