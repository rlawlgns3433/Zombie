#pragma once
#include "GameObject.h"
class Tilemap : public GameObject
{
protected :
	sf::VertexArray va;
	sf::Texture* texture;

	std::string spriteSheetId;

	sf::Vector2i cellCount = { 10, 10 }; // ¸ã Å©±â
	sf::Vector2f cellSize;

public :
	Tilemap(const std::string& name = "");

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Translate(const sf::Vector2f& delta) override;

	void Set(const sf::Vector2i& cellCount, const sf::Vector2f& cellSize);
	void SetPosition(const sf::Vector2f& pos) override;
	void SetPosition(float x, float y) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& origin) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetFlipX(bool flip) override;
	void SetFlipY(bool flip) override;

	void SetSpriteSheedId(const std::string& id);
};