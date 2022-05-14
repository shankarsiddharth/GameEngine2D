#pragma once
#include <vector>
#include "Math/Vector2.h"

struct GameConstants
{
	const float PlayerForce = 2.5f;

	const float ObstacleRotaionSpeed = 0.5f;

	const Vector2 PlayerPosition = Vector2(-525.0f, -350.0f);

	const std::vector<Vector2> WidthBoundaryPositions = {
		Vector2(0.0f, -400.0f),
		Vector2(0.0f, 384.0f)
	};

	const std::vector<Vector2> HeightBoundaryPositions = {
		Vector2(-592.0f, -400.0f),
		Vector2(592.0f, -400.0f)
	};

	const std::vector<Vector2> CollectiblePositions = {
		Vector2(-300.0f, -100.0f)
	};

	const std::vector<Vector2> ObstaclePositions = {
		Vector2(0.0f, 250.0f),
		Vector2(0.0f, 50.0f),
		Vector2(0.0f, -250.0f)
	};

	const std::vector<Vector2> WallPositions = {
		Vector2(-552.0f, 75.0f),
		Vector2(-488.0f, 75.0f),
		Vector2(-424.0f, 75.0f),
		Vector2(-360.0f, 75.0f),
		Vector2(-232.0f, 75.0f),
		Vector2(-232.0f, 139.0f),
		Vector2(-232.0f, 203.0f),
		Vector2(-232.0f, 267.0f)
	};

	const std::vector<Vector2> BreakableWallPositions = {
		Vector2(-296.0f, 75.0f),
		Vector2(-525.0f, -150.0f),
		Vector2(-232.0f, 331.0f)
	};
};