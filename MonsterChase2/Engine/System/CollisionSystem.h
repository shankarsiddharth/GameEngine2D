#pragma once
#include <vector>

class GameWorld;
class BoxCollider2D;

class CollisionSystem
{
public:
	CollisionSystem();
	~CollisionSystem();

	void Initialize();
	void Update(float deltaTime, GameWorld* i_GameWorld);
	void ShutDown();

private:
	void SeparatingAxisCheck(const std::vector<BoxCollider2D*>& InBoxColliderList);
	bool DoesInterect(BoxCollider2D& A, BoxCollider2D& B);
};

