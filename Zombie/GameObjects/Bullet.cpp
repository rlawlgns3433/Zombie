#include "pch.h"
#include "Bullet.h"


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
}

void Bullet::Release()
{
    GameObject::Release();
}

void Bullet::Reset()
{
    GameObject::Reset();
}

void Bullet::Update(float dt)
{
    GameObject::Update(dt);

    shape.setPosition(Utils::Vector2::MoveTowards(
        shape.getPosition(),
        direction * 3000.f,
        speed * dt));

    if (Utils::MyMath::Distance(shape.getPosition(), SCENE_MANAGER.GetCurrentScene()->FindGameObject("player")->GetPosition()) > 1000.f)
    {
        SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(this);
    }
}

void Bullet::Draw(sf::RenderWindow& window)
{
    GameObject::Draw(window);
    window.draw(shape);
}
