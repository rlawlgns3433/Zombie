#pragma once
#include "Item.h"
#include "HealthBox.h"

class HealthBar;

// 픽업 아이템
class HealthBox : public Item
{
protected:
	HealthBox(const HealthBox&) = delete;
	HealthBox(HealthBox&&) = delete;
	HealthBox& operator=(const HealthBox&) = delete;
	HealthBox& operator=(HealthBox&&) = delete;

	HealthBar* healthBar = nullptr;

public:
	static unsigned amount;
	static int healthboxCnt;
	static HealthBox* Create(ItemType BulletType = ItemType::None);

	HealthBox(const std::string& name = "");
	~HealthBox() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

