#include "pch.h"
#include "Gun.h"

Gun::Gun(const std::string& name)
	: GameObject(name)
{
	
}

void Gun::Init()
{
	GameObject::Init();
	gunCapacity = 100;
	gunAmmo = 6;
	currentAmmo = 6;
	gunDelay = 2.f;
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

	if (availShoot)
	{
		Bullet* bullet = new Bullet("bullet");
		bullet->direction = SCENE_MANAGER.GetCurrentScene()->ScreenToWorld((sf::Vector2i)(InputManager::GetMousePos() - SCENE_MANAGER.GetCurrentScene()->FindGameObject("player")->GetPosition()));
		SCENE_MANAGER.GetCurrentScene()->AddGameObject(bullet);

		availShoot = false;
		time = 0;
	}

}

void Gun::Reload()
{
	if (gunCapacity < 0)
	{
		gunCapacity += currentAmmo;
		currentAmmo -= gunAmmo;
	}
}
