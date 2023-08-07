#include "Frog.h"

Frog::Frog() : m_units(1), m_scale(1), m_dx(0.0f), m_dy(0.0f), m_moving(false), m_speed(4)
{}

Frog::Frog(float unit, float scale, ResourceManager& resourceManager) : m_units(1.0f), m_scale(1.0f), m_dx(0.0f), m_dy(0.0f), m_moving(false), m_speed(4)
{
	m_scale = scale;
	m_units = unit;
	trans.SetPosition(0, (m_units * 13));
	trans.SetScale(m_scale);
	resourceManager.LoadImageFromFile(frogs, "../Assets/spritesheet.png");
	currSprite.SetImage(frogs);
	coll.SetSize((int)(unit / 2), (int)(unit / 2));
	coll.SetPosition((int)(trans.position.x + m_units / 4), (int)(trans.position.y + m_units / 4));

	sit.SetImage(frogs);
	jump.SetImage(frogs);

	sit.SetSource(1, 1, 16, 16);
	jump.SetSource(19, 1, 16, 16);
	currSprite = sit;
	targetPos = trans.position;
}

void Frog::updateFrog(float dt)
{
	if (m_moving)
	{
		if (m_dx > 0)
		{
			currSprite = jump;
			trans.SetRotation(90);
			if (trans.position.x < targetPos.x) { trans.position.x += m_dx; }
			else { trans.position.x = targetPos.x; m_moving = false; currSprite = sit; m_dx = 0; m_dy = 0; }
		}

		else if (m_dx < 0)
		{
			currSprite = jump;
			trans.SetRotation(270);
			if (trans.position.x > targetPos.x) { trans.position.x += m_dx; }
			else { trans.position.x = targetPos.x; m_moving = false; currSprite = sit; m_dx = 0; m_dy = 0; }
		}

		else if (m_dy > 0)
		{
			currSprite = jump;
			trans.SetRotation(180);
			if (trans.position.y < targetPos.y) { trans.position.y += m_dy; }
			else { trans.position.y = targetPos.y; m_moving = false; currSprite = sit; m_dx = 0; m_dy = 0; }
		}

		else if (m_dy < 0)
		{
			currSprite = jump;
			trans.SetRotation(0);
			if (trans.position.y > targetPos.y) { trans.position.y += m_dy; }
			else { trans.position.y = targetPos.y; m_moving = false; currSprite = sit; m_dx = 0; m_dy = 0; }
		}
		coll.SetPosition((int)(trans.position.x + m_units / 4), (int)(trans.position.y + m_units / 4));
	}
}

Frog::~Frog()
{}

void Frog::renderFrog(RenderManager& rendererManager)
{
	rendererManager.Render(currSprite, trans);
}

void Frog::OnKeyDown(KeyCode key)
{
	if (!m_moving)
	{
		switch (key)
		{
			case KeyCode::LEFT_ARROW:

				m_dx = -1 * m_speed;
				m_dy = 0;
				m_moving = true;
				targetPos.x = trans.position.x - m_units;
				return;
				break;

			case KeyCode::RIGHT_ARROW:

				m_dx = 1 * m_speed;
				m_dy = 0;
				m_moving = true;
				targetPos.x = trans.position.x + m_units;

				return;
				break;

			case KeyCode::DOWN_ARROW:

				m_dy = 1 * m_speed;
				m_dx = 0;
				m_moving = true;
				targetPos.y = trans.position.y + m_units;

				return;
				break;

			case KeyCode::UP_ARROW:

				m_dy = -1 * m_speed;
				m_dx = 0;
				m_moving = true;
				targetPos.y = trans.position.y - m_units;

				return;
				break;

			default:
				break;
		}
	}
}