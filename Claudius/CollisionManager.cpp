#include "CollisionManager.h"
#include "Collider.h"

bool CollisionManager::CheckCollision(Collider& lhs, Collider& rhs)
{
	if (lhs.rect.x + lhs.rect.w < rhs.rect.x ||
		lhs.rect.x > rhs.rect.x + rhs.rect.w ||
		lhs.rect.y + lhs.rect.h < rhs.rect.y ||
		lhs.rect.y > rhs.rect.y + rhs.rect.h)
	{
		return false;
	}
	return true;
}
