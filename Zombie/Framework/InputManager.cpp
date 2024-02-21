#include "InputManager.h"
#include "pch.h"
#include <algorithm>

std::map<Axis, AxisInfo> InputManager::axisInfoMap;
//std::unordered_map<std::unordered_map<sf::Keyboard::Key, sf::Time>, bool> InputManager::downKeyMap;
//std::unordered_map<std::unordered_map<sf::Keyboard::Key, sf::Time>, bool> InputManager::upKeyMap;
//std::unordered_map<std::unordered_map<sf::Keyboard::Key, sf::Time>, bool> InputManager::ingKeyMap;

std::list<sf::Keyboard::Key> InputManager::downKeyList;
std::list<sf::Keyboard::Key> InputManager::upKeyList;
std::list<sf::Keyboard::Key> InputManager::ingKeyList;

sf::Mouse InputManager::mouse;

void InputManager::Init()
{

	// Horizontal
	AxisInfo infoHorizontal;
	infoHorizontal.axis = Axis::Horizontal;
	infoHorizontal.positives.push_back(sf::Keyboard::D);
	infoHorizontal.positives.push_back(sf::Keyboard::Right);
	infoHorizontal.negatives.push_back(sf::Keyboard::A);
	infoHorizontal.negatives.push_back(sf::Keyboard::Left);
	infoHorizontal.sensitive = 5.f;
	infoHorizontal.value = 0.f;

	axisInfoMap[infoHorizontal.axis] = infoHorizontal;

	// Vertical
	AxisInfo infoVertcal;
	infoVertcal.axis = Axis::Vertical;
	infoVertcal.positives.push_back(sf::Keyboard::S);
	infoVertcal.positives.push_back(sf::Keyboard::Up);
	infoVertcal.negatives.push_back(sf::Keyboard::W);
	infoVertcal.negatives.push_back(sf::Keyboard::Down);
	infoVertcal.sensitive = 5.f;
	infoVertcal.value = 0.f;

	axisInfoMap[infoVertcal.axis] = infoVertcal;
}

void InputManager::Update(float dt)
{
	for (auto& pair : axisInfoMap)
	{
		AxisInfo& axisInfo = pair.second;

		float raw = GetAxisRaw(axisInfo.axis);
		float speed = raw;
		if (speed == 0.f && axisInfo.value != 0.f)
		{
			speed = axisInfo.value > 0.f ? -1.f : 1.f;
		}
		axisInfo.value += speed * axisInfo.sensitive * dt;
		axisInfo.value = Utils::Clamp(axisInfo.value, -1.f, 1.f);

		if (raw == 0.f && abs(axisInfo.value) < speed * axisInfo.sensitive * dt)
		{
			axisInfo.value = 0.f;
		}
	}
}

void InputManager::UpdateEvent(const sf::Event& event)
{
	// 해당 키가 리스트에 없다면 눌린 첫 프레임
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (!GetKey(event.key.code))
		{
			//downKeyMap[(sf::Keyboard::Key)EncryptKey(event.key.code)] = true;
			//ingKeyMap[(sf::Keyboard::Key)EncryptKey(event.key.code)] = true;
			downKeyList.push_back(event.key.code);
			ingKeyList.push_back(event.key.code);
		}
		break;

	case sf::Event::KeyReleased:
		//ingKeyMap[(sf::Keyboard::Key)EncryptKey(event.key.code)] = false;
		//upKeyMap[(sf::Keyboard::Key)EncryptKey(event.key.code)] = true;
		ingKeyList.remove(event.key.code);
		upKeyList.push_back(event.key.code);
		break;

	case sf::Event::MouseButtonPressed:
		if (!GetMouseButton(event.mouseButton.button))
		{
			sf::Keyboard::Key button = MouseButtonToKey(event.mouseButton.button);
			downKeyList.push_back(button);
			ingKeyList.push_back(button);
		}
		break;
	case sf::Event::MouseButtonReleased:
		sf::Keyboard::Key button = MouseButtonToKey(event.mouseButton.button);
		ingKeyList.remove(button);
		upKeyList.push_back(button);
		break;
	}
}

void InputManager::Clear()
{
	downKeyList.clear();
	upKeyList.clear();
}

bool InputManager::GetKeyDown(sf::Keyboard::Key key)
{
	//return downKeyMap[key];

	return std::find(downKeyList.begin(), downKeyList.end(), key) != downKeyList.end();
}

bool InputManager::GetKeyUp(sf::Keyboard::Key key)
{
	//return upKeyMap[key];
	return std::find(upKeyList.begin(), upKeyList.end(), key) != upKeyList.end();
	 
}

bool InputManager::GetKey(sf::Keyboard::Key key)
{
	//return ingKeyMap[key];
	return std::find(ingKeyList.begin(), ingKeyList.end(), key) != ingKeyList.end();

}

float InputManager::GetAxisRaw(Axis axis)
{
	auto findInfo = axisInfoMap.find(axis);
	if (findInfo == axisInfoMap.end())
	{
		return 0.f;
	}

	const auto& info = findInfo->second;
	auto it = ingKeyList.rbegin();
	while (it != ingKeyList.rend())
	{
		sf::Keyboard::Key key = *it;

		if (std::find(info.positives.begin(), info.positives.end(), key) != info.positives.end())
		{
			return 1.f;
		}

		if (std::find(info.negatives.begin(), info.negatives.end(), key) != info.negatives.end())
		{
			return -1.f;
		}

		++it;
	}

	return 0.0f;
}

float InputManager::GetAxis(Axis axis)
{
	auto findInfo = axisInfoMap.find(axis);
	if (findInfo == axisInfoMap.end())
	{
		return 0.f;
	}

	return findInfo->second.value;
}


sf::Vector2f InputManager::GetMousePos()
{
	return (sf::Vector2f)mouse.getPosition();
}

bool InputManager::GetMouseButtonDown(sf::Mouse::Button mouse)
{
	return std::find(downKeyList.begin(), downKeyList.end(), MouseButtonToKey(mouse)) != downKeyList.end();
}

bool InputManager::GetMouseButtonUp(sf::Mouse::Button mouse)
{
	return std::find(upKeyList.begin(), upKeyList.end(), MouseButtonToKey(mouse)) != upKeyList.end();
}

bool InputManager::GetMouseButton(sf::Mouse::Button mouse)
{
	return std::find(ingKeyList.begin(), ingKeyList.end(), MouseButtonToKey(mouse)) != ingKeyList.end();
}



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
