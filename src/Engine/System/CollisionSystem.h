#pragma once
#include <vector>
#include <functional>
#include "../SmartPointer/SmartPointer.h"
#include "../Object/GameObject.h"

class GameWorld;
class BoxCollider2D;

typedef std::function<void(SharedPointer<GameObject>, SharedPointer<GameObject>)> FOnCollisionDetected;

class CollisionSystem
{
public:
	CollisionSystem();
	~CollisionSystem();

	void Initialize();
	void Update(float InDeltaTime, GameWorld* InGameWorld);
	void ShutDown();

	void ListenForCollisions(FOnCollisionDetected InOnCollisionDetectedCallback);

protected:
	FOnCollisionDetected m_OnCollisionDetected;

private:
	void SeparatingAxisCheck(const std::vector<BoxCollider2D*>& InBoxColliderList, float InDeltaTime);
	bool DoesInterect(BoxCollider2D& InA, BoxCollider2D& InB, float InDeltaTime);
};

