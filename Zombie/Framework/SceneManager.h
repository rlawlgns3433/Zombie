#pragma once
#include "Singleton.h"

class Scene; 

enum class SceneIDs
{
	None = -1,
	SceneGame,
	COUNT, // Scene의 개수
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
	
	void Init(); // 의도한 시점에 생성 또는 소멸시킬 수 있도록 함수를 정의
	void Release(); // 의도한 시점에 생성 또는 소멸시킬 수 있도록 함수를 정의

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