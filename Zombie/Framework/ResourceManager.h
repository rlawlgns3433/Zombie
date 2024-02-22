#pragma once
#include "Singleton.h"

template <typename T>
class ResourceManager : public Singleton<ResourceManager<T>> // ���ø� Ŭ����
{
protected:
	std::unordered_map<std::string, T*> resourceMap;
	friend class Singleton<ResourceManager<T>>;

public:
	ResourceManager(const ResourceManager& ref)				= delete;
	ResourceManager(ResourceManager&& ref)					= delete;
	ResourceManager& operator=(const ResourceManager& ref)	= delete;
	ResourceManager& operator=(ResourceManager&& ref)		= delete;

	static T Empty;
	ResourceManager() = default;
	virtual ~ResourceManager()
	{
		UnloadAll();
	}

	bool Load(const std::string& filePath) // ���ҽ� ���ε�
	{
		if(resourceMap.find(filePath) != resourceMap.end())
		{
			return false;
		}

		T* resource = new T();

		bool isSuccess = resource->loadFromFile(filePath);

		if (isSuccess)
		{
			resourceMap[filePath] = resource;
		}

		return isSuccess;
	}
	void UnloadAll()
	{
		for (const auto& pair : resourceMap) // pair�� Ÿ���� pair�̴�.
		{
			delete pair.second; // ��ü ���� �Ҵ� ���� �� ��° ��Ҹ� �Ҵ� ����
		}

		resourceMap.clear(); // �ؽ� �� ���� ����
	}
	bool Unload(const std::string& filePath) // ���ҽ� ��ε�
	{
		auto it = resourceMap.find(filePath);
		if (it == resourceMap.end())
		{
			return false;
		}
		
		delete it->second;
		resourceMap.erase(it);
		return true;
	}
	T* GetResource(const std::string& filePath, bool load = true) // ���ҽ� ã��
	{
		auto it = resourceMap.find(filePath);

		if (it != resourceMap.end())
		{
			return it->second;
		}
		
		if (!load || !Load(filePath))
		{
			return nullptr;
		}

		return resourceMap.find(filePath)->second;
	}
};

template <typename T>
T ResourceManager<T>::Empty;  // ���� ���� �ʱ�ȭ

#define FONT_MANAGER (Singleton<ResourceManager<sf::Font>>::Instance())
#define TEXTURE_MANAGER (Singleton<ResourceManager<sf::Texture>>::Instance())
#define SOUND_MANAGER (Singleton<ResourceManager<sf::SoundBuffer>>::Instance())