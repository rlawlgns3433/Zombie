#include "Utils.h"
#include "pch.h"

#pragma region Security Area
//int Utils::p = Utils::GenerateRandomPrime();
//int Utils::q = Utils::GenerateRandomPrime();
//int Utils::n = p * q;
//int Utils::z = (p - 1) * (q - 1);
//int Utils::e = Utils::GetPublicKeyExponent(z);
//int Utils::d = Utils::GetPrivateKeyExponent(e, z);
#pragma endregion

float Utils::Clamp(float value, float min, float max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

sf::Vector2f Utils::ClampMagnitude(sf::Vector2f vector, float maxLength)
{
	float sqrtMag = SqrMagnitude(vector);
	if (sqrtMag > maxLength * maxLength)
	{
		sf::Vector2f normalized = GetNormal(vector);
		return sf::Vector2f(normalized.x * maxLength, normalized.y * maxLength);
	}
	return vector;
}

float Utils::RandomValue()
{
	return (float)rand() / RAND_MAX;
}

float Utils::RandomRange(float min, float max)
{
	float value = RandomValue();
	value *= (max - min);
	value += min;

	return value;
}

sf::Vector2f Utils::RandomOnUnitCircle()
{
	sf::Transform rotation;
	rotation.rotate(RandomRange(0, 360));
	return rotation * sf::Vector2f{ 1.f, 0.f };
}

sf::Vector2f Utils::RandomInUnitCircle()
{
	return RandomOnUnitCircle() * RandomValue();
}

sf::Vector2f Utils::SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect)
{
	sf::Vector2f newOrigin(rect.width, rect.height);
	newOrigin.x *= ((int)originPreset % 3) * 0.5f; // 0 1 2 => 0 0.5 1
	newOrigin.y *= ((int)originPreset / 3) * 0.5f; // 0 1 2 => 0 0.5 1
	obj.setOrigin(newOrigin);

	return newOrigin;
}

sf::Vector2f Utils::SetOrigin(sf::Sprite& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Text& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());

}

sf::Vector2f Utils::SetOrigin(sf::Shape& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());
}

sf::Vector2f Utils::Min(const sf::Vector2f& vector1, const sf::Vector2f& vector2)
{
	return sf::Vector2f(std::min(vector1.x, vector2.x), std::min(vector1.y, vector2.y));
}

sf::Vector2f Utils::Max(const sf::Vector2f& vector1, const sf::Vector2f& vector2)
{
	return sf::Vector2f(std::max(vector1.x, vector2.x), std::max(vector1.y, vector2.y));
}

float Utils::Magnitude(const sf::Vector2f vector)
{
	return vector.x * vector.x + vector.y * vector.y;
}

float Utils::SqrMagnitude(const sf::Vector2f vector)
{
	return std::sqrt(Magnitude(vector));
}

void Utils::Normalize(sf::Vector2f& vector)
{
	float magnitude = Magnitude(vector);

	if (magnitude != 0.f)
	{
		vector /= magnitude;
	}
}
// 벡터를 벡터의 길이로 나누어 1로 정규화 시킴
sf::Vector2f Utils::GetNormal(const sf::Vector2f& vector)
{
	float magnitude = Magnitude(vector);

	if (magnitude == 0.f)
	{
		return vector;
	}
	return vector / Magnitude(vector);
}

float Utils::Distance(const sf::Vector2f& src, const sf::Vector2f& dst)
{
	return Magnitude(dst - src);
}

float Utils::Angle(const sf::Vector2f look)
{
	return Rad2Deg(std::atan2f(look.y, look.x));
}

float Utils::SignedAngle(const sf::Vector2f& from, const sf::Vector2f& to)
{
	float unsignedAngle = std::acos(Dot(from, to)) / (Magnitude(from) * Magnitude(to));
	float sign = from.x * to.y - to.x * from.y < 0.f ? -1.f : 1.f;

	return Rad2Deg(sign * unsignedAngle);
}

float Utils::Rad2Deg(float radian)
{
	return radian * (180.f / M_PI);
}

float Utils::Deg2Rad(float degree)
{
	return degree * (M_PI / 180.f);
}

float Utils::Dot(const sf::Vector2f& vector1, const sf::Vector2f& vector2)
{
	return vector1.x * vector2.x + vector1.y * vector2.y;
}

sf::Vector2f Utils::Lerp(const sf::Vector2f& src, const sf::Vector2f& dst, float deltaTime)
{
	return sf::Vector2f(src.x + (dst.x - src.x) * deltaTime, src.y + (dst.y - src.y) * deltaTime);
}

sf::Vector2f Utils::MoveTowards(const sf::Vector2f& current, const sf::Vector2f& target, float maxDistanceDelta)
{
	sf::Vector2f direction = target - current;
	float distance = Magnitude(direction);
	if (distance <= maxDistanceDelta || distance == 0.f)
	{
		return target;
	}
	return current + (direction / distance) * maxDistanceDelta;
}

sf::Vector2f Utils::Perpendicular(const sf::Vector2f& vector)
{
	return sf::Vector2f(-vector.y, vector.x);
}

sf::Vector2f Utils::Reflect(const sf::Vector2f& inDirection, const sf::Vector2f& inNormal)
{
	return sf::Vector2f(inDirection - 2.f * Dot(inDirection, inNormal) * inNormal);
}

sf::Vector2f Utils::Scale(const sf::Vector2f& vector1, const sf::Vector2f& vector2)
{
	return sf::Vector2f(vector1.x * vector2.x, vector1.y * vector2.y);
}

sf::Vector2f Utils::GetRandomVector2(float start, float end)
{
	float randVal = (rand() % ((int)(end * 100) - (int)(start * 100))) + start * 100;
	return sf::Vector2f(randVal / 100, randVal / 100);
}


float Utils::GetRandomAngle()
{
	return (float)rand() / RAND_MAX * 360.f;
}

#pragma region  Security Area

//int InputManager::EncryptKey(sf::Keyboard::Key key)
//{
//	int p = Utils::GenerateRandomPrime();
//	int q = Utils::GenerateRandomPrime();
//	int n = p * q;
//	int z = (p - 1) * (q - 1);
//	int e = Utils::GetPublicKeyExponent(z);
//	int d = Utils::GetPrivateKeyExponent(e, z);
//	return Utils::Encrypt((int)key, e, n);
//}
//
//sf::Keyboard::Key InputManager::DecryptKey(int cipherText)
//{
//	int p = Utils::GenerateRandomPrime();
//	int q = Utils::GenerateRandomPrime();
//	int n = p * q;
//	int z = (p - 1) * (q - 1);
//	int e = Utils::GetPublicKeyExponent(z);
//	int d = Utils::GetPrivateKeyExponent(e, z);
//	return (sf::Keyboard::Key)(Utils::Decrypt(cipherText, d, n));
//}




//
//int Utils::GetGCD(int a, int b)
//{
//	int temp;
//	if (a < b) {
//		temp = a;
//		a = b;
//		b = temp;
//	}
//	if (b == 0)
//		return a;
//	else {
//		return GetGCD(b, a % b);
//	}
//}
//
//int Utils::GetPrivateKeyExponent(int exponent, int z)
//{
//	exponent = exponent % z;
//	for (int i = 1; i < z; i++)
//		if ((exponent * i) % z == 1)
//			return i;
//	return 1;
//}
//
//int Utils::Encrypt(int message, int exponent, int n)
//{
//	int result = 1;
//	message = message % n;
//	while (exponent > 0) {
//		if (exponent % 2 == 1)
//			result = (result * message) % n;
//		exponent = exponent / 2;
//		message = (message * message) % n;
//	}
//	return result;
//}
//
//int Utils::Decrypt(int cipherText, int exponent, int n)
//{
//	int result = 1;
//	cipherText = cipherText % n;
//	while (exponent > 0) {
//		if (exponent % 2 == 1)
//			result = (result * cipherText) % n;
//		exponent = exponent / 2;
//		cipherText = (cipherText * cipherText) % n;
//	}
//	return result;
//}
//
//bool Utils::IsPrime(int number)
//{
//	if (number == 1) return false;
//	if (number == 2 || number == 3) return true;
//	for (int i = 2; i < number; i++) {
//		if (number % i == 0) return false;
//	}
//	return true;
//}
//
//int Utils::GenerateRandomPrime(int min, int max)
//{
//	srand(time(NULL));
//
//	int primeNumber = (rand() % min + 1) + max;
//	while (!IsPrime(primeNumber))
//		primeNumber = (rand() % min + 1) + max;
//
//	return primeNumber;
//}
//
//int Utils::GetPublicKeyExponent(int exponent)
//{
//	int e = SHRT_MAX;
//
//	while (GetGCD(e, exponent) != 1) e++;
//
//	return e;
//}
#pragma endregion
