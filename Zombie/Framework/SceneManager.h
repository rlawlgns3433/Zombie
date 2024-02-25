#pragma once
#include "Singleton.h"

class Scene; 

enum class SceneIDs
{
	None = -1,
	SceneTitle,
	SceneGame,
	SceneSkillUp,
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
	SceneIDs startScene = SceneIDs::SceneTitle;
	SceneIDs currentScene = startScene;

	std::vector<std::string> TextureResourceNames = { };
	std::vector<std::string> FontResourceNames = { "fonts/DS-DIGI.ttf" };
	std::vector<std::string> SoundResourceNames = { "sound/hit.wav", "sound/pickup.wav", "sound/reload.wav" , "sound/reload.wav", "sound/reload_failed.wav", "sound/shoot.wav" ,"sound/splat.wav" };

	unsigned lives = 3;
	unsigned score = 0;

public:

	SceneManager() = default;
	virtual ~SceneManager();
	
	void Init(); // �ǵ��� ������ ���� �Ǵ� �Ҹ��ų �� �ֵ��� �Լ��� ����
	void Release(); // �ǵ��� ������ ���� �Ǵ� �Ҹ��ų �� �ֵ��� �Լ��� ����

	Scene* GetCurrentScene() { return scenes[(int)currentScene]; }
	Scene* GetScene(SceneIDs id) { return scenes[(int)id]; }
	
	void LoadAllResources();
	void ChangeScene(SceneIDs id);
	void Update(float dt);
	void LateUpdate(float dt);
	void FixeUpdate(float dt);
	void Draw(sf::RenderWindow& window);
};

#define SCENE_MANAGER (Singleton<SceneManager>::Instance())