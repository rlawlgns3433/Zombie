#pragma once
#include "SpriteGo.h"
class CrossHair : public SpriteGo
{
protected :
	CrossHair(const CrossHair&)				= delete;
	CrossHair(CrossHair&&)					= delete;
	CrossHair& operator=(const CrossHair&)	= delete;
	CrossHair& operator=(CrossHair&&)		= delete;
	
	std::string textureId = "graphics/crosshair.png";

public :
	CrossHair(const std::string& name = "");
	~CrossHair() override					= default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

