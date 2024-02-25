#include "pch.h"
#include "Gun.h"
#include "SceneGame.h"

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

	sceneGame = dynamic_cast<SceneGame*>(SCENE_MANAGER.GetCurrentScene());
	player = dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("player"));
}

void Gun::Update(float dt)
{
	GameObject::Update(dt);
	reloadTimer += dt;

	if (InputManager::GetKeyDown(sf::Keyboard::R))
	{
		reloadTimer = 0;
		isReload = true;
	}

	if (isReload && reloadTimer > reloadDelay)
	{
		Reload();
		isReload = false;
	}

	if (!availShoot)
	{
		fireTimer += dt;
		if (fireTimer > gunDelay)
		{
			availShoot = true;
		}
	}
}

void Gun::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
}

void Gun::Fire()
{
	if (availShoot && currentGunAmmo > 0 && !isReload)
	{
		Bullet* bullet = new Bullet("bullet");
		bullet->Init();
		bullet->Reset();
		bullet->SetDirection(SCENE_MANAGER.GetCurrentScene()->ScreenToWorld((sf::Vector2i)(InputManager::GetMousePos() - player->GetPosition())));
		sceneGame->AddGameObject(bullet);

		sound.resetBuffer();
		sound.setBuffer(*SOUND_MANAGER.GetResource("sound/shoot.wav"));
		sound.play();

		availShoot = false;
		--currentGunAmmo;
		fireTimer = 0;
	}
}

void Gun::Reload()
{
	if (currentGunCapacity > 0)
	{
		currentGunCapacity += currentGunAmmo;

		if (currentGunCapacity >= gunAmmo)
		{
			currentGunCapacity -= gunAmmo;
			currentGunAmmo = gunAmmo;
		}
		else
		{
			currentGunAmmo += currentGunCapacity;
			currentGunCapacity = 0;
		}

		sound.resetBuffer();
		sound.setBuffer(*SOUND_MANAGER.GetResource("sound/reload.wav"));
		sound.play();
	}
}
