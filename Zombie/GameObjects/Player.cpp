#include "pch.h"
#include "Player.h"

Player::Player(const std::string& name)
	: SpriteGo(name)
{
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);

	gun = new Gun("gun");
	gun->Init();
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(gun); // position ¾øÀ½

	crossHair = dynamic_cast<CrossHair*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("crosshair"));
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();
	SetPosition({ 0, 0 });
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	time += dt;


	switch (SCENE_MANAGER.GetCurrentScene()->GetStatus())
	{
	case GameStatus::Awake:
		break;
	case GameStatus::Game:
	{
		if (InputManager::GetMouseButton(sf::Mouse::Left))
		{
			gun->Fire();
		}


		if (time > damageInterval)
		{
			if (!nowDamage)
			{
				for (int i = 0; i < Zombie::zombieCnt; ++i)
				{
					GameObject* obj = SCENE_MANAGER.GetCurrentScene()->FindGameObject("zombie" + std::to_string(i));
					if (obj != nullptr)
					{
						if (Utils::MyMath::Distance(position, obj->GetPosition()) < 100.f)
						{
							hp -= 20;
							nowDamage = true;
							time = 0;
							return;
						}
					}

				}
			}
			else
			{
				nowDamage = false;
			}
		}




		sf::Vector2i mousePosition = (sf::Vector2i)InputManager::GetMousePos();
		sf::Vector2f mouseWorldPosition = SCENE_MANAGER.GetCurrentScene()->ScreenToWorld(mousePosition);

		look = mouseWorldPosition - position;
		Utils::MyMath::Normalize(look);

		SetRotation(Utils::MyMath::Angle(look));

		direction.x = InputManager::GetAxis(Axis::Horizontal);
		direction.y = InputManager::GetAxis(Axis::Vertical);

		if (Utils::MyMath::Magnitude(direction) > 1.f)
		{
			Utils::MyMath::Normalize(direction);
		}

		Translate(direction * speed * dt);

		std::cout << "hp : " << hp << std::endl;

		break;
	}
	case GameStatus::GameOver:
		break;
	case GameStatus::Pause:
		break;
	}


}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
