#pragma once
class Utils
{
private:
#pragma region Security Areaa
	//static int p;
	//static int q;
	//static int n;
	//static int z;
	//static int e;
	//static int d;
#pragma endregion

public:

	// Random
	static float RandomValue(); // 0.0 ~ 1.0
	static float RandomRange(float min, float max);
	static sf::Vector2f RandomOnUnitCircle();
	static sf::Vector2f RandomInUnitCircle();
	static sf::Vector2f GetRandomVector2(float start, float end);
	static float GetRandomAngle();

	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect);
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Shape& obj, Origins originPreset);

	// Math
	static sf::Vector2f Min(const sf::Vector2f& vector1, const sf::Vector2f& vector2);
	static sf::Vector2f Max(const sf::Vector2f& vector1, const sf::Vector2f& vector2);

	static float Magnitude(const sf::Vector2f vector); // ±Ê¿Ã
	static float SqrMagnitude(const sf::Vector2f vector); // ±Ê¿Ã ¡¶∞ˆ±Ÿ
	static void Normalize(sf::Vector2f& vector); // ø¯∫ª ∫§≈Õ¿« ±Ê¿Ã∏¶ 1∑Œ πŸ≤€ ∫§≈Õ
	static sf::Vector2f GetNormal(const sf::Vector2f& vector);// ∫§≈Õ¿« ±Ê¿Ã∏¶ 1∑Œ πŸ≤€ ∫§≈Õ

	static float Distance(const sf::Vector2f& src, const sf::Vector2f& dst);
	static float Angle(const sf::Vector2f look);
	static float SignedAngle(const sf::Vector2f& from, const sf::Vector2f& to);
	static float Rad2Deg(float radian);
	static float Deg2Rad(float degree);
	static float Dot(const sf::Vector2f& vector1, const sf::Vector2f& vector2);
	static sf::Vector2f Lerp(const sf::Vector2f& src, const sf::Vector2f& dst, float deltaTime);
	static sf::Vector2f MoveTowards(const sf::Vector2f& current, const sf::Vector2f& target, float maxDistanceDelta);
	static sf::Vector2f Perpendicular(const sf::Vector2f& vector);
	static sf::Vector2f Reflect(const sf::Vector2f& inDirection, const sf::Vector2f& inNormal);
	static sf::Vector2f Scale(const sf::Vector2f& vector1, const sf::Vector2f& vector2);


	static float Clamp(float value, float min, float max);
	static sf::Vector2f ClampMagnitude(sf::Vector2f vector, float maxLength);

#pragma region Security Area
	//static int EncryptKey(sf::Keyboard::Key key);
	//static sf::Keyboard::Key DecryptKey(int cipherText);	
	//static int GetGCD(int a, int b);
	//static int GetPrivateKeyExponent(int exponent, int z);
	//static int Encrypt(int message, int exponent, int n);
	//static int Decrypt(int cipherText, int exponent, int n);
	//static bool IsPrime(int number);
	//static int GenerateRandomPrime(int min = 2, int max = 200);
	//static int GetPublicKeyExponent(int exponent);
#pragma endregion
};