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
	SCENE_MANAGER.GetScene(SceneIDs::SceneGame)->AddGameObject(gun);

	crossHair = dynamic_cast<CrossHair*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("crosshair"));

	healthBar = new HealthBar("healthbar");
	healthBar->SetFillColor(sf::Color::Red);
	healthBar->SetPosition({FRAMEWORK.GetWindowSize().x * 0.5f, FRAMEWORK.GetWindowSize().y * 0.9f });
	healthBar->SetOrigin(Origins::MC);
	SCENE_MANAGER.GetScene(SceneIDs::SceneGame)->AddGameObject(healthBar, Layers::Ui);

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
						if (Utils::MyMath::Distance(position, obj->GetPosition()) < 30.f)
						{
							hp -= 20 * 4; // 좀비 데미지 적용 필요
							healthBar->SetRectSize({ hp, healthBar->GetRectSize().y });
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

		cellCountX = 15;
		cellCountY = 15;
		cellSizeX = TEXTURE_MANAGER.GetResource("graphics/background_sheet.png")->getSize().x; // 50
		cellSizeY = TEXTURE_MANAGER.GetResource("graphics/background_sheet.png")->getSize().y / 4; // 50


		float leftEdge = -cellSizeX * cellCountX * 0.5f + cellSizeX;
		float rightEdge = cellCountX * cellSizeX - cellSizeX * cellCountX * 0.5f - cellSizeX;
		float topEdge = -cellSizeY * cellCountY * 0.5f + cellSizeY;
		float bottomEdge = cellCountY * cellSizeY - cellSizeY * cellCountY * 0.5f - cellSizeY;

		position.x = std::max(leftEdge, std::min(rightEdge, position.x));
		position.y = std::max(topEdge, std::min(bottomEdge, position.y));

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
