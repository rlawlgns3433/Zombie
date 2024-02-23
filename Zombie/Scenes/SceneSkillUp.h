#pragma once
#include "Scene.h"

class SpriteGo;
class TextGo;
class Player;
class Gun;

class SceneSkillUp : public Scene
{
protected:
	SceneSkillUp(const SceneSkillUp&)			 = delete;
	SceneSkillUp(SceneSkillUp&&)				 = delete;
	SceneSkillUp& operator=(const SceneSkillUp&) = delete;
	SceneSkillUp& operator=(SceneSkillUp&&)		 = delete;

	std::vector<std::string> skillTextNames = {
		"1-INCREASED RATE OF FIRE",
		"2-INCREASED CLIP SIZE(NEXT RELOAD)",
		"3-INCREASED MAX HEALTH",
		"4-INCREASED RUN SPEED",
		"5-MORE AND BETTER HEALTH PICKUPS",
		"6-MORE AND BETTER AMMO PICKUPS"
	};

	Player* player = nullptr;
	Gun* gun = nullptr;

	SpriteGo* spriteGoBackground = nullptr;
	TextGo* text = nullptr;

	float windowX = 0.f;
	float windowY = 0.f;

	float time = 0.f;

public:
	SceneSkillUp(SceneIDs id);
	~SceneSkillUp() override					 = default;

	void Init() override;
	void Release() override;
	virtual void Reset();
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};