#pragma once
#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <unordered_map>

enum class Axis
{
	Horizontal,
	Vertical,
};

struct AxisInfo
{
	Axis axis;

	std::list<sf::Keyboard::Key> positives;
	std::list<sf::Keyboard::Key> negatives;

	float sensitive;
	float value;
};

// 키보드 입력뿐 아니라 마우스 입력까지 추가 필요
class InputManager
{
private:
	//sf::Clock clock;
	//sf::Time currentTime; 
	static std::map<Axis, AxisInfo> axisInfoMap;

	// 이번 프레임에 down인 키들을 담아두는 맵, 눌린 키를 맵에 모두 담아서 처리 // 시간정보를 저장하여 가장 최근에 눌린 키를 기준으로 동작하게 바꿔야 한다.
	//static std::unordered_map<std::unordered_map<sf::Keyboard::Key, sf::Time>, bool> downKeyMap;
	//static std::unordered_map<std::unordered_map<sf::Keyboard::Key, sf::Time>, bool> upKeyMap;
	//static std::unordered_map<std::unordered_map<sf::Keyboard::Key, sf::Time>, bool> ingKeyMap;

	static std::list<sf::Keyboard::Key> downKeyList;
	static std::list<sf::Keyboard::Key> upKeyList;
	static std::list<sf::Keyboard::Key> ingKeyList;

	// 한 프레임 내에서 keydown, keyup이 보장이 되어야 한다. 하나의 프레임 내에서만!
public:

	static sf::Mouse mouse;
	static void Init();
	static void Update(float dt);

	static void UpdateEvent(const sf::Event& event);
	static void Clear();
	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);

	static sf::Vector2f GetMousePos();

	static bool GetMouseButtonDown(sf::Mouse::Button mouse);
	static bool GetMouseButtonUp(sf::Mouse::Button mouse);
	static bool GetMouseButton(sf::Mouse::Button mouse);

	static float GetAxisRaw(Axis axis); // -1.f  /  0.f  /  1.f
	static float GetAxis(Axis axis); // -1.f ~ 1.f

	static sf::Keyboard::Key MouseButtonToKey(sf::Mouse::Button button) { return (sf::Keyboard::Key)(button + sf::Keyboard::Key::KeyCount); };
	static sf::Mouse::Button KeytoMouseButton(sf::Keyboard::Key key) { return (sf::Mouse::Button)(key + sf::Keyboard::Key::KeyCount); };

	//static int EncryptKey(sf::Keyboard::Key key);
	//static sf::Keyboard::Key DecryptKey(int cipherText);
};