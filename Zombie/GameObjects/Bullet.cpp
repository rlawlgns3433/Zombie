#include "pch.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "Zombie.h"

Bullet::Bullet(const std::string& name)
    : GameObject(name)
{
    shape.setFillColor(sf::Color::White);
    shape.setRadius(5.f);
    shape.setPosition(dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("player"))->GetPosition());
    SetOrigin(Origins::MC);
}

void Bullet::Init()
{
    GameObject::Init();
    player = dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("player"));
    crossHair = dynamic_cast<CrossHair*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("crosshair"));
    sceneGame = dynamic_cast<SceneGame*>(SCENE_MANAGER.GetCurrentScene());
}

void Bullet::Release()
{
    GameObject::Release();
}

void Bullet::Reset()
{
    GameObject::Reset();
    sceneGame = dynamic_cast<SceneGame*>(SCENE_MANAGER.GetCurrentScene());
}

void Bullet::Update(float dt)
{
    GameObject::Update(dt);

    shape.setPosition(Utils::Vector2::MoveTowards(shape.getPosition(), direction * 3000.f,speed * dt));

    if (sceneGame != nullptr)
    {
        if (!sceneGame->IsInTilemap(shape.getPosition()))
        {
            SetActive(false);
            sceneGame->RemoveGameObject(this);
        }
    }
}

void Bullet::FixedUpdate(float dt)
{
    auto& list = sceneGame->GetZombieList();
    for (auto& obj : list)
    {
        if (dynamic_cast<Zombie*>(obj)->IsDead()) continue;

        if (GetGlobalBounds().intersects(obj->GetGlobalBounds()))
        {
            SetActive(false);
            sceneGame->RemoveGameObject(this);

            Zombie* zombie = dynamic_cast<Zombie*>(obj);
            if (zombie != nullptr)
            {
                zombie->OnDamage(damage);
                
                sound.resetBuffer();
                sound.setBuffer(*SOUND_MANAGER.GetResource("sound/hit.wav"));
                sound.play();
            }
            break;
        }
    }
}

void Bullet::Draw(sf::RenderWindow& window)
{
    GameObject::Draw(window);
    window.draw(shape);
}
