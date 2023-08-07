#pragma once

#include "Vector2.h"

struct Transform
{
	Transform();
	Transform(const Transform& rhs);
	
	void SetPosition(const float x, const float y);
	void SetRotation(const float rotation);
	void SetScale(const float scale);

	void ChangePosition(const float x, const float y);
	void ChangeRotation(const float rotation);
	void ChangeScale(const float scale);

	Vector2 GetPosition();
	float GetRotation();
	float GetScale();

	Vector2 position;
	float rotation;
	float scale;
};