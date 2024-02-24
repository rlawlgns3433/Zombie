#include "pch.h"
#include "Gun.h"
#include "SceneGame.h"

int Gun::gunCount = 0;

Gun::Gun(const std::string& name)
	: GameObject(name)
{
}

void Gun::Init()
{
	GameObject::Init();

	time = 0.f;
	availShoot = true;
	gunCapacity = 6;	// 전체 총알 수 
	currentGunCapacity = 6;
	gunAmmo = 6;		// 한 탄창
	currentAmmo = 6; // 내 현재 탄창

	gunDelay = 2.f;
	reloadDelay = 0.8f;
	isReload = false;


}

void Gun::Release()
{
	GameObject::Release();
}

void Gun::Reset()
{
	GameObject::Reset();
	time = 0.f;
	availShoot = true;
	gunCapacity = 6;	// 전체 총알 수 
	currentGunCapacity = 6;
	gunAmmo = 6;		// 한 탄창
	currentAmmo = 6; // 내 현재 탄창


	gunDelay = 2.f;
	reloadDelay = 0.8f;
	isReload = false;

	sceneGame = dynamic_cast<SceneGame*>(SCENE_MANAGER.GetCurrentScene());
	player = dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("player"));
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
		bullet->Init();
		bullet->Reset();
		bullet->direction = SCENE_MANAGER.GetCurrentScene()->ScreenToWorld((sf::Vector2i)(InputManager::GetMousePos() - player->GetPosition()));
		sceneGame->AddGameObject(bullet);

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
