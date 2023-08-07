#pragma once

struct Collider;

struct CollisionManager
{
	static bool CheckCollision(Collider &lhs, Collider &rhs);
};
