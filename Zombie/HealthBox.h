#pragma once
#include "Item.h"
#include "HealthBox.h"

// �Ⱦ� ������
class HealthBox : public Item
{
protected:
	HealthBox(const HealthBox&) = delete;
	HealthBox(HealthBox&&) = delete;
	HealthBox& operator=(const HealthBox&) = delete;
	HealthBox& operator=(HealthBox&&) = delete;

	unsigned amount = 40;

public:
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

