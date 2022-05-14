#pragma once
#include <vector>
#include "Math/Vector2.h"

struct GameConstants
{
	const float PlayerForce = 0.5f;

	const float ObstacleRotaionSpeed = 0.5f;

	const std::vector<Vector2> WidthBoundaryPositions = {
		Vector2(),
		Vector2()
	};

	const std::vector<Vector2> HeightBoundaryPositions = {
		Vector2(),
		Vector2()
	};

	const std::vector<Vector2> ObstaclePositions = {
		Vector2(),
		Vector2(),
		Vector2(),
		Vector2()
	};

	const std::vector<Vector2> WallPositions = {
		Vector2(),
		Vector2(),
		Vector2(),
		Vector2(),
		Vector2(),
		Vector2(),
		Vector2()
	};

	const std::vector<Vector2> BreakableWallPositions = {
		Vector2(),
		Vector2(),
		Vector2()
	};
};