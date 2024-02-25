#include "pch.h"
#include "Player.h"
#include "SceneGame.h"

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
	gun->Reset();
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
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MANAGER.GetCurrentScene());
	SetPosition({ 0, 0 });

	invincibleTime = 1.f;
	invincibleTimer = 0.f;

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

		sf::Vector2f pos = position + direction * speed * dt;
		if (sceneGame != nullptr)
		{
			pos = sceneGame->ClampByTilemap(pos);
		}
		SetPosition(pos);


		if (InputManager::GetMouseButton(sf::Mouse::Left))
		{
			gun->Fire();
		}

		healthBar->SetRectSize({ hp, healthBar->GetRectSize().y });

		if (isInvincible)
		{
			invincibleTimer += dt;
			if (invincibleTimer > invincibleTime)
			{
				isInvincible = false;
			}
		}

		break;
	}
	case GameStatus::GameOver:
		break;
	case GameStatus::Pause:
		break;
	}
}

void Player::LateUpdate(float dt)
{
}

void Player::FixedUpdate(float dt)
{


}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Player::OnDamage(int damage)
{
	if (isDead || isInvincible) return;

	hp -= damage;
	isInvincible = true;
	invincibleTimer = 0.f;

	if (hp <= 0)
	{
		hp = 0;
		OnDie();
	}
}

void Player::OnDie()
{
	if (isDead)
		return;

	isDead = false;
	sceneGame->SetStatus(GameStatus::GameOver);
}
