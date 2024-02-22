#include "pch.h"
#include "Origin.h"

namespace Utils
{
	sf::Vector2f Origin::SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect)
	{
		sf::Vector2f newOrigin(rect.width, rect.height);
		newOrigin.x *= ((int)originPreset % 3) * 0.5f; // 0 1 2 => 0 0.5 1
		newOrigin.y *= ((int)originPreset / 3) * 0.5f; // 0 1 2 => 0 0.5 1
		obj.setOrigin(newOrigin);

		return newOrigin;
	}

	sf::Vector2f Origin::SetOrigin(sf::Sprite& obj, Origins originPreset)
	{
		return SetOrigin(obj, originPreset, obj.getLocalBounds());
	}

	sf::Vector2f Origin::SetOrigin(sf::Text& obj, Origins originPreset)
	{
		return SetOrigin(obj, originPreset, obj.getLocalBounds());

	}

	sf::Vector2f Origin::SetOrigin(sf::Shape& obj, Origins originPreset)
	{
		return SetOrigin(obj, originPreset, obj.getLocalBounds());
	}
}