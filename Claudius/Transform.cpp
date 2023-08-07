#include "Transform.h"

Transform::Transform() : position(), rotation(0.0f), scale(1.0f)
{
}

Transform::Transform(const Transform& rhs) : position(rhs.position), rotation(rhs.rotation), scale(rhs.scale)
{
}

void Transform::SetPosition(const float x, const float y)
{
	position.x = x;
	position.y = y;
}

void Transform::SetRotation(const float rotation)
{
	this->rotation = rotation;
}

void Transform::SetScale(const float scale)
{
	this->scale = scale;
}

void Transform::ChangePosition(const float x, const float y)
{
	position.x += x;
	position.y += y;
}

void Transform::ChangeRotation(const float rotation)
{
	this->rotation += rotation;
}

void Transform::ChangeScale(const float scale)
{
	this->scale += scale;
}

Vector2 Transform::GetPosition()
{
	return position;
}

float Transform::GetRotation()
{
	return rotation;
}

float Transform::GetScale()
{
	return scale;
}
