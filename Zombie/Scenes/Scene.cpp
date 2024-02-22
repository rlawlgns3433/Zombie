#include "pch.h"
#include "Scene.h"

Scene::Scene(SceneIDs id) : id(id), textureManager(ResourceManager<sf::Texture>::Instance()), fontManager(ResourceManager<sf::Font>::Instance()),
soundManager(ResourceManager<sf::SoundBuffer>::Instance())
{
}

void Scene::Init()
{
	for (GameObject* obj : gameObjects)
	{
		obj->Init();
	}

	for (GameObject* obj : uiGameObjects)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	for (GameObject* obj : gameObjects)
	{
		delete obj;
	}

	for (GameObject* obj : uiGameObjects)
	{
		delete obj;
	}

	gameObjects.clear();
	uiGameObjects.clear();
}

void Scene::Enter()
{
	for (GameObject* obj : gameObjects)
	{
		obj->Reset();
	}

	for (GameObject* obj : uiGameObjects)
	{
		obj->Reset();
	}
}

void Scene::Update(float dt)
{
	for (GameObject* obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}

	for (GameObject* obj : uiGameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}

	for (GameObject* obj : resortingGameObjects)
	{
		auto it = std::find(gameObjects.cbegin(), gameObjects.cend(), obj);
		if (it != gameObjects.end())
		{
			gameObjects.remove(obj);
			AddGameObject(obj, Layers::World);
			continue;
		}

		it = std::find(uiGameObjects.cbegin(), uiGameObjects.cend(), obj);
		if (it != uiGameObjects.end())
		{
			uiGameObjects.remove(obj);
			AddGameObject(obj, Layers::Ui);
			continue;
		}
	}

	resortingGameObjects.clear();

	for (GameObject* obj : removeGameObjects)
	{
		gameObjects.remove(obj);
		uiGameObjects.remove(obj);

		delete obj;
		obj = nullptr;
	}

	removeGameObjects.clear();
}

void Scene::Draw(sf::RenderWindow& window)
{
	//gameObjects.sort(Utils::Sort::sortGameObject);
	//uiGameObjects.sort(Utils::Sort::sortGameObject);


	const sf::View& saveView = window.getView();

	window.setView(worldView);
	for (auto& obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}
	
	window.setView(uiView);
	for (auto& obj : uiGameObjects)
	{
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}

	window.setView(saveView); // ���� ������ ��� �����ֱ�
}

GameObject* Scene::FindGameObject(const std::string& name, Layers layer)
{
	if ((layer & Layers::World) == Layers::World)
	{
		for (auto obj : gameObjects)
		{
			if (obj->GetName() == name)
			{
				return obj;
			}
		}
	}

	if ((layer & Layers::Ui) == Layers::Ui)
	{
		for (auto obj : uiGameObjects)
		{
			if (obj->GetName() == name)
			{
				return obj;
			}
		}
	}

	return nullptr;
}

std::list<GameObject*>& Scene::FindAllGameObjectwithName(const std::string& name, Layers layer)
{
	std::list<GameObject*> list;

	if ((layer & Layers::World) == Layers::World)
	{
		for (auto obj : gameObjects)
		{
			if (obj->GetName() == name)
			{
				list.push_back(obj);
			}
		}
	}

	if ((layer & Layers::Ui) == Layers::Ui)
	{
		for (auto obj : uiGameObjects)
		{
			if (obj->GetName() == name)
			{
				list.push_back(obj);
			}
		}
	}
	return list;
}

int Scene::FindAll(const std::string& name, std::list<GameObject*>& list, Layers layer)
{
	list.clear();
	if ((layer & Layers::World) == Layers::World)
	{
		for (auto gameObject : gameObjects)
		{
			if (gameObject->GetName() == name)
			{
				list.push_back(gameObject);
			}
		}
	}

	if ((layer & Layers::Ui) == Layers::Ui)
	{
		for (auto gameObject : uiGameObjects)
		{
			if (gameObject->GetName() == name)
			{
				list.push_back(gameObject);
			}
		}
	}

	return list.size();
}

GameObject* Scene::AddGameObject(GameObject* obj, Layers layer)
{
	if (layer == Layers::World)
	{
		if (std::find(gameObjects.begin(), gameObjects.end(), obj) == gameObjects.end())
		{
			auto it = gameObjects.begin();
			while (it != gameObjects.end())
			{
				if (GameObject::CompareDrawOrder(obj, *it))
				{
					gameObjects.insert(it, obj);
					return obj;
				}
				++it;
			}
			gameObjects.push_back(obj);				// ����Ʈ�� �ƹ��͵� ��� ��ȸ�� �� �ϸ� �߰�
			return obj;
		}
	}

	if (layer == Layers::Ui)
	{
		if (std::find(uiGameObjects.begin(), uiGameObjects.end(), obj) == uiGameObjects.end())
		{
			auto it = uiGameObjects.begin();
			while (it != uiGameObjects.end())
			{
				if (GameObject::CompareDrawOrder(obj, *it))
				{
					uiGameObjects.insert(it, obj);
					return obj;
				}
				++it;
			}
			uiGameObjects.push_back(obj);				// ����Ʈ�� �ƹ��͵� ��� ��ȸ�� �� �ϸ� �߰�
			return obj;
		}
	}

	return nullptr;
}

GameObject* Scene::AddGameObject(const std::string& name, Layers layer)
{
	GameObject* obj = FindGameObject(name);
	if (layer == Layers::World)
	{
		if (std::find(gameObjects.begin(), gameObjects.end(), obj) == gameObjects.end())
		{
			auto it = gameObjects.begin();
			while (it != gameObjects.end())
			{
				if (GameObject::CompareDrawOrder(obj, *it))
				{
					gameObjects.insert(it, obj);
					return obj;
				}
				++it;
			}
			gameObjects.push_back(obj);				// ����Ʈ�� �ƹ��͵� ��� ��ȸ�� �� �ϸ� �߰�
			return obj;
		}
	}

	if (layer == Layers::Ui)
	{
		if (std::find(uiGameObjects.begin(), uiGameObjects.end(), obj) == uiGameObjects.end())
		{
			auto it = uiGameObjects.begin();
			while (it != uiGameObjects.end())
			{
				if (GameObject::CompareDrawOrder(obj, *it))
				{
					uiGameObjects.insert(it, obj);
					return obj;
				}
				++it;
			}
			uiGameObjects.push_back(obj);				// ����Ʈ�� �ƹ��͵� ��� ��ȸ�� �� �ϸ� �߰�
			return obj;
		}
	}

	return nullptr;
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
	if (std::find(removeGameObjects.begin(), removeGameObjects.end(), gameObject) == removeGameObjects.end())
	{
		removeGameObjects.push_back(gameObject);
	}
}

void Scene::RemoveGameObject(std::string name)
{
	removeGameObjects.push_back(FindGameObject(name));
}

void Scene::ResortGameObject(GameObject* obj)
{
	resortingGameObjects.push_back(obj);
}

sf::Vector2f Scene::ScreenToWorld(sf::Vector2i screenPosition)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPosition, worldView);
}

sf::Vector2i Scene::WorldToScreen(sf::Vector2f worldPosition)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(worldPosition, worldView);
}

sf::Vector2f Scene::ScreenToUi(sf::Vector2i screenPosition)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPosition, uiView);
}

sf::Vector2i Scene::UiToScreen(sf::Vector2f uiPosition)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(uiPosition, uiView);
}

void Scene::SetStatus(GameStatus newStatus)
{
	GameStatus prevStatus = status;

	status = newStatus;

	switch (status)
	{
	case GameStatus::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case GameStatus::Game:
		FRAMEWORK.SetTimeScale(1.f);
		break;
	case GameStatus::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case GameStatus::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	}
}
