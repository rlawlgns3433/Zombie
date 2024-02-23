#include "pch.h"
#include "Gun.h"

int Gun::gunCount = 0;

Gun::Gun(const std::string& name)
	: GameObject(name)
{
}

void Gun::Init()
{
	GameObject::Init();
}

void Gun::Release()
{
	GameObject::Release();
}

void Gun::Reset()
{
	GameObject::Reset();
}

void Gun::Update(float dt)
{
	GameObject::Update(dt);
	time += dt;

	if (InputManager::GetKeyDown(sf::Keyboard::R))
	{
		time = 0;
		isReload = true;
	}

	if (isReload && time > reloadDelay)
	{
		Reload();
		isReload = false;
	}
}

void Gun::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
}

void Gun::Fire()
{
	if (time > gunDelay)
	{
		availShoot = true;
	}

	if (availShoot && currentAmmo > 0)
	{
		Bullet* bullet = new Bullet("bullet");
		bullet->direction = SCENE_MANAGER.GetCurrentScene()->ScreenToWorld((sf::Vector2i)(InputManager::GetMousePos() - SCENE_MANAGER.GetCurrentScene()->FindGameObject("player")->GetPosition()));
		SCENE_MANAGER.GetCurrentScene()->AddGameObject(bullet);

		availShoot = false;
		--currentAmmo;
		time = 0;
	}
}

void Gun::Reload()
{
	// 로직 수정 필요
	if (currentGunCapacity > 0) // gunCapacity를 수정하면 안 됨
	{
		currentGunCapacity += currentAmmo;

		currentAmmo = gunAmmo;

		currentGunCapacity -= gunAmmo;
	}
}
