#pragma once
#include "Image.h"
#include "Collider.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "KeyCode.h"
#include "Sprite.h"
#include "Transform.h"
#include <vector>

struct Car
{
	public:
		Transform trans;
		Image cars;
		Sprite sprite;
		Collider coll;
		Color color;
		Car(float unit, float scale, ResourceManager& resourceManager);
		void pushCar(float spd, int lane, int row, bool twoWide);
		void updateCars(float dt);
		void renderCars(RenderManager& rendererManager);
		float m_units;
		float m_scale;
		float m_speed;
		float m_speed2;
		int m_length;
};