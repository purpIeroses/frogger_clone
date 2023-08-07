#include "Log.h"

Log::Log(float unit, float scale, ResourceManager& resourceManager) :
	m_speed(1), m_speed2(0.3f), m_length(1)
{
	m_scale = scale;
	m_units = unit;
	resourceManager.LoadImageFromFile(logs, "../Assets/spritesheet.png");
}

void Log::pushLog(float spd, int lane, int row, int length)
{
	m_speed = spd;
	trans.SetPosition(row * m_units, (7 * m_units) - lane * m_units);
	trans.SetScale(m_scale);

	if (length < 3 || m_length > 6)
	{
		length = 3;
	}
	m_length = length;

	coll.SetSize((int)(length * (int)m_units), (int)m_units);
	sprite.SetImage(logs);
	switch (m_length)
	{
	case 3:
		sprite.SetSource(1, 19, 16 * 3, 16);
		break;
	case 4:
		sprite.SetSource(1, 37, 16 * 4, 16);
		break;
	case 5:
		sprite.SetSource(1, 55, 16 * 5, 16);
		break;
	case 6:
		sprite.SetSource(1, 73, 16 * 6, 16);
		break;
	default:
		break;
	}
}

void Log::updateLogs(float dt)
{
	trans.position.x += m_speed * m_speed2;
	coll.SetPosition((int)trans.position.x, (int)trans.position.y);
	if (trans.position.x > (14 * m_units) && m_speed > 0)
	{
		trans.position.x = (m_units * -1 * m_length);
	}
	else if (trans.position.x < (m_units * -1 * m_length) && m_speed < 0)
	{
		trans.position.x = (14 * m_units);
	}
}

void Log::renderLogs(RenderManager& rendererManager)
{
	rendererManager.Render(sprite, trans);
}