#pragma once

enum class Origins
{
	TL,
	TC,
	TR,
	ML,
	MC,
	MR,
	BL,
	BC,
	BR,
	CUSTOM,
};

enum class Sides
{
	NONE = -1,
	LEFT,
	RIGHT,
	COUNT
};

enum class PlayerSelectCharacter
{
	None = -1,
	WoodCutter,
	YoungWoodCutter,
	COUNT,
};

enum class PlayerState
{
	NOTSET = -1,
	ALIVE,
	DEAD
};

enum class GameStatus
{
	Awake,
	Game,
	GameOver,
	Pause,
};
