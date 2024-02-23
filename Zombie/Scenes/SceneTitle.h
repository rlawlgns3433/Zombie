#pragma once

class SpriteGo;
class TextGo;

class SceneTitle : public Scene
{
protected:
	SceneTitle(const SceneTitle&)			 = delete;
	SceneTitle(SceneTitle&&)				 = delete;
	SceneTitle& operator=(const SceneTitle&) = delete;
	SceneTitle& operator=(SceneTitle&&)		 = delete;

	SpriteGo* spriteGoBackground = nullptr;
	TextGo* textIntro = nullptr;
	TextGo* textHighScore = nullptr;

	float windowX = 0.f;
	float windowY = 0.f;

	float blinkTime = 0.7f;
	float time = 0.f;

public:
	SceneTitle(SceneIDs id);
	~SceneTitle() override					 = default;

	void Init() override;
	void Release() override;
	virtual void Reset();
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void BlinkIntro(float blinkTime);
};