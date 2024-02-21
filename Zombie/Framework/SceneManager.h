#pragma once
#include "Singleton.h"

class Scene; 

enum class SceneIDs
{
	None = -1,
	SceneGame,
	COUNT, // Scene�� ����
};

class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;

public:

protected:
	SceneManager(const SceneManager&)			 = delete;
	SceneManager(SceneManager&&)				 = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager& operator=(SceneManager&&)		 = delete;

	std::vector<Scene*> scenes;
	SceneIDs startScene = SceneIDs::SceneGame;
	SceneIDs currentScene = startScene;

	std::vector<std::string> TextureResourceNames = { };
	std::vector<std::string> FontResourceNames = { "fonts/DS-DIGI.ttf" };
	std::vector<std::string> SoundResourceNames = {};

	unsigned lives = 3;
	unsigned score = 0;

public:

	SceneManager() = default;
	virtual ~SceneManager();
	
	void Init(); // �ǵ��� ������ ���� �Ǵ� �Ҹ��ų �� �ֵ��� �Լ��� ����
	void Release(); // �ǵ��� ������ ���� �Ǵ� �Ҹ��ų �� �ֵ��� �Լ��� ����

	Scene* GetCurrentScene() { return scenes[(int)currentScene]; }
	
	void LoadAllResources();
	void ChangeScene(SceneIDs id);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	void SetScore(unsigned score) { this->score = score; }
	void SetLives(unsigned lives) { this->lives = lives; }

	unsigned GetScore() const { return this->score; }
	unsigned GetLives() const { return this->lives; }
};

#define SCENE_MANAGER (Singleton<SceneManager>::Instance())