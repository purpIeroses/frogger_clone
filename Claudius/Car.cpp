#include "Car.h"

Car::Car(float unit, float scale, ResourceManager& resourceManager) 
	: m_speed(1), m_speed2(0.5f), m_length(0)
{
	m_scale = scale;
	m_units = unit;
	resourceManager.LoadImageFromFile(cars, "../Assets/spritesheet.png");	
}

void Car::pushCar(float spd, int lane, int row, bool twoWide)
{
	m_speed = spd;
	trans.SetPosition(row * m_units, (13 * m_units) - lane * m_units);
	trans.SetScale(m_scale);
	sprite.SetImage(cars);
	if (twoWide)
	{
		coll.SetSize(2 * (int)m_units, (int)m_units);
		m_length = 2;
	}
	else
	{
		coll.SetSize((int)m_units, (int)m_units);
		m_length = 1;
	}
	color.SetColor(0, 255, 0, 0);

	switch (lane)
	{
	case 1:
		sprite.SetSource(55, 1, 16, 16);
		break;
	case 2:
		sprite.SetSource(91, 1, 16, 16);
		break;
	case 3:
		sprite.SetSource(37, 1, 16, 16);
		break;
	case 4:
		sprite.SetSource(73, 1, 16, 16);
		break;
	case 5:
		sprite.SetSource(109, 1, 32, 16);
		break;
	default:
		break;
	}
}

void Car::updateCars(float dt)
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

void Car::renderCars(RenderManager& rendererManager)
{
	rendererManager.Render(sprite, trans);
}