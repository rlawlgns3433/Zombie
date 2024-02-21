#include "pch.h"
#include "Tilemap.h"

Tilemap::Tilemap(const std::string& name)
	: GameObject(name)
{
}

void Tilemap::Init()
{
	GameObject::Init();
	SetSpriteSheedId("graphics/background_sheet.png");
	Set({ 15,15 }, { 50,50 });
	SetOrigin(Origins::BR);
}

void Tilemap::Release()
{
	GameObject::Release();
}

void Tilemap::Reset()
{
	GameObject::Reset();
}

void Tilemap::Update(float dt)
{
	GameObject::Update(dt);
}

void Tilemap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{
	this->cellCount = count;
	this->cellSize = size;

	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4); // 셀의 개수 * 정점의 개수

	sf::Vector2f posOffsets[4] =
	{
		{ 0, 0 },
		{ size.x, 0 },
		{ size.x, size.y },
		{ 0, size.y }
	};

	sf::Vector2f textureCoord0[4] = // 현재는 하드코딩 -> 변경 필요 (각 타일의 크기로)
	{
		{ 0, 0 },
		{ cellSize.x, 0 },
		{ cellSize.x, cellSize.y },
		{ 0, cellSize.y }
	};

	for (int row = 0; row < count.y; ++row)
	{
		for (int col = 0; col < count.x; ++col)
		{
			int textureIndex = Utils::RandomRange(0, 3);

			if (row == 0 || row == count.y - 1 || col == 0 || col == count.x - 1)
			{
				textureIndex = 3;
			}

			int quadIndex = row * count.x + col;
			sf::Vector2f quadPos(position.x + size.x * col, position.y + size.y * row);

			for (int vertex = 0; vertex < 4; ++vertex)
			{
				int vertexIndex = (quadIndex * 4) + vertex;

				va[vertexIndex].position = quadPos + posOffsets[vertex];
				va[vertexIndex].texCoords = textureCoord0[vertex];
				va[vertexIndex].texCoords.y += textureIndex * cellSize.y;
			}
		}
	}
}

void Tilemap::Translate(const sf::Vector2f& delta)
{
	
}

void Tilemap::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);

	window.draw(va, texture);
}

void Tilemap::SetPosition(const sf::Vector2f& pos)
{
	sf::Vector2f delta = pos - position;
	for (int i = 0; i < va.getVertexCount(); ++i)
	{
		va[i].position += delta;
	}

	position = pos;
}

void Tilemap::SetPosition(float x, float y)
{
	sf::Vector2f delta = sf::Vector2f(x, y) - position;
	for (int i = 0; i < va.getVertexCount(); ++i)
	{
		va[i].position += delta;
	}

	position = { x, y };
}

void Tilemap::SetOrigin(Origins preset)
{
	originPreset = preset;

	for (int i = 0; i < va.getVertexCount(); ++i)
	{
		sf::Vector2f offset = { cellCount.x * cellSize.x * ((int)originPreset % 3) * 0.5f, cellCount.y * cellSize.y * ((int)originPreset / 3) * 0.5f };

		va[i].position -= offset;
	}
}

void Tilemap::SetOrigin(const sf::Vector2f& origin)
{
	originPreset = Origins::CUSTOM;
	this->origin - origin;

	for (int i = 0; i < va.getVertexCount(); ++i)
	{
		sf::Vector2f offset = { cellCount.x * cellSize.x * ((int)originPreset % 3) * 0.5f, cellCount.y * cellSize.y * ((int)originPreset / 3) * 0.5f };

		va[i].position -= offset;
	}
}

void Tilemap::SetScale(const sf::Vector2f& scale)
{
}

void Tilemap::SetFlipX(bool flip)
{
}

void Tilemap::SetFlipY(bool flip)
{
}

void Tilemap::SetSpriteSheedId(const std::string& id)
{
	this->spriteSheetId = id;
	this->texture = TEXTURE_MANAGER.GetResource(spriteSheetId);
}
