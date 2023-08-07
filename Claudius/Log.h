#pragma once
#include "Image.h"
#include "Collider.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "KeyCode.h"
#include "Sprite.h"
#include "Transform.h"
#include <vector>

struct Log
{
	public:
		Transform trans;
		Image logs;
		Sprite sprite;
		Collider coll;
		Log(float unit, float scale, ResourceManager& resourceManager);
		void pushLog(float spd, int lane, int row, int length);
		void updateLogs(float dt);
		void renderLogs(RenderManager& rendererManager);
		float m_units;
		float m_scale;
		float m_speed;
		float m_speed2;
		int m_length;
};