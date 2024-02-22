#include "pch.h"
#include "MyMath.h"

namespace Utils
{
	float MyMath::Magnitude(const sf::Vector2f vector)
	{
		return std::sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	float MyMath::SqrMagnitude(const sf::Vector2f vector)
	{
		return vector.x * vector.x + vector.y * vector.y;
	}

	void MyMath::Normalize(sf::Vector2f& vector)
	{
		float magnitude = Magnitude(vector);

		if (magnitude != 0.f)
		{
			vector /= magnitude;
		}
	}
	
	sf::Vector2f MyMath::GetNormal(const sf::Vector2f& vector)
	{
		float magnitude = Magnitude(vector);

		if (magnitude == 0.f)
		{
			return vector;
		}
		return vector / Magnitude(vector);
	}

	float MyMath::Distance(const sf::Vector2f& src, const sf::Vector2f& dst)
	{
		return Magnitude(dst - src);
	}

	float MyMath::Angle(const sf::Vector2f look)
	{
		return Rad2Deg(std::atan2f(look.y, look.x));
	}

	float MyMath::Rad2Deg(float radian)
	{
		return radian * (180.f / M_PI);
	}

	float MyMath::Deg2Rad(float degree)
	{
		return degree * (M_PI / 180.f);
	}

	float MyMath::Clamp(float value, float min, float max)
	{
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}
}
