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

	//fireTimer = 0.f;
	//reloadTimer = 0.f;
	//availShoot = true;
	//gunCapacity = 6;	// ��ü �Ѿ� �� 
	//currentGunCapacity = 6;
	//gunAmmo = 6;		// �� źâ
	//currentGunAmmo = 6; // �� ���� źâ

	//gunDelay = 2.f;
	//reloadDelay = 0.8f;
	//isReload = false;
}

void Gun::Release()
{
	GameObject::Release();
}

void Gun::Reset()
{
	GameObject::Reset();
	//reloadTimer = 0.f;
	//fireTimer = 0.f;
	//availShoot = true;
	//gunCapacity = 6;	// ��ü �Ѿ� �� 
	//currentGunCapacity = 6;
	//gunAmmo = 6;		// �� źâ
	//currentGunAmmo = 6; // �� ���� źâ

	//gunDelay = 2.f;
	//reloadDelay = 0.8f;
	//isReload = false;

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

	std::cout << "��ü ź�� �� : " << currentGunCapacity << std::endl;
	std::cout << "�� ���� źâ : " << currentGunAmmo << std::endl;
	std::cout << "��߻� �ð�  : " << gunDelay << std::endl;
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
		bullet->direction = SCENE_MANAGER.GetCurrentScene()->ScreenToWorld((sf::Vector2i)(InputManager::GetMousePos() - player->GetPosition()));
		sceneGame->AddGameObject(bullet);

		availShoot = false;
		--currentGunAmmo;
		fireTimer = 0;
	}
}

void Gun::Reload()
{
	// ���� ���� �ʿ�
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
		}
	}
}
