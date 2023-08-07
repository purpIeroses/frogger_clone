#pragma once
#include "Sprite.h"
#include "Transform.h"
#include "Collider.h"
#include "Image.h"
#include "KeyCode.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Transform.h"
#include "Collider.h"
#include "Image.h"
#include "KeyCode.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include <vector>

struct RenderManager;
struct ResourceManager;

struct Frog
{
	public:
		Sprite currSprite;
		Sprite sit;
		Sprite jump;
		Transform trans;
		Collider coll;
		Image frogs;
		Frog();
		Frog(float units, float scale, ResourceManager& resourceManager);
		~Frog();
		void updateFrog(float dt);
		void renderFrog(RenderManager& rendererManager);
		void OnKeyDown(KeyCode key);
		float m_units;
		float m_scale;
		float m_dx;
		float m_dy;
		float m_speed;
		bool m_moving;
		Vector2 targetPos;
};