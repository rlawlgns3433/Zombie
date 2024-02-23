#include "pch.h"
#include "HealthBar.h"

HealthBar::HealthBar(const std::string& name)
	: GameObject(name)
{
	rectCurrentSize = rectSize;
	rectShape.setSize(rectCurrentSize);
}

void HealthBar::Update(float dt)
{

}

void HealthBar::Reset()
{
	rectCurrentSize = rectSize;
	SetRectSize(rectCurrentSize);
}

void HealthBar::Draw(sf::RenderWindow& window)
{
	window.draw(rectShape);
}

void HealthBar::SetRectSize(const sf::Vector2f& size)
{
	this->rectCurrentSize = size;
	rectShape.setSize(size);
}

void HealthBar::SetFillColor(const sf::Color& color)
{
	rectShape.setFillColor(color);
}

void HealthBar::SetPosition(const sf::Vector2f& pos)
{
	rectShape.setPosition(pos);
}

void HealthBar::SetOrigin(Origins preset)
{

	if (preset == Origins::CUSTOM)
	{
		preset == Origins::TL;
	}

	originPreset = preset;
	Utils::Origin::SetOrigin(rectShape, originPreset);
}

void HealthBar::AddTime(float size)
{
	this->rectCurrentSize.x += size;
	rectShape.setSize(this->rectCurrentSize);
}
