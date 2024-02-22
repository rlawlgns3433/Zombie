#pragma once
#include "SpriteGo.h"
#include "Player.h"

class Item : public SpriteGo
{
protected :
	Item(const Item&)				= delete;
	Item(Item&&)					= delete;
	Item& operator=(const Item&)	= delete;
	Item& operator=(Item&&)			= delete;

	Player* player;
	ItemType type = ItemType::None;

public :
	Item(const std::string& name = "");
	~Item() override				= default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

