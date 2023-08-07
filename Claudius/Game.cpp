//Sophia Al-Nawasreh
//help with collision and game tilemapping was received from Casper Gustavsson
#include "Game.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include <iostream>

Game::Game(ResourceManager& resourceManager) : m_resourceManager(resourceManager), Width(224), m_scale(3.0f), playing(true)
{
	Width *= m_scale;
	m_units = Width / 14.0f;
	Height = m_units * 14.0f;
	resourceManager.LoadImageFromFile(bg, "../Assets/bg.png");
	resourceManager.LoadImageFromFile(sheet, "../Assets/spritesheet");
	bgSprite.SetSource(0, 0, 224, 216);
	bgSprite.SetImage(bg);
	bgTrans.SetPosition(0, m_units / 2);
	bgTrans.SetScale(m_scale);
	frog = new Frog(m_units, m_scale, resourceManager);

	for (int i = 0; i < 12; i++)
	{
		Car* tempCar = new Car(m_units, m_scale, resourceManager);
		cars.push_back(tempCar);
	}

	loadCars();

	for (int i = 0; i < 16; i++)
	{
		Log* tempLog = new Log(m_units, m_scale, resourceManager);
		logs.push_back(tempLog);
	}

	loadLogs();

	for (int i = 0; i < 3; i++)
	{
		Health* tempHP = new Health();
		tempHP->sprites = frog->sit;
		tempHP->trans.SetPosition((float)i * m_units * 0.5f, 0.0f);
		tempHP->trans.SetScale(m_scale * 0.5f);
		playerHealth.push_back(tempHP);
	}
}

Game::~Game()
{
	frog->~Frog();
}

bool Game::Enter(int& width, int& height, std::string& title)
{
	width = (int)Width;
	height = (int)Height;
	title = "Frogger";
	return true;
}

bool Game::Update(float dt)
{
	for (Car* c : cars)
	{ 
		c->updateCars(dt);
	}
	for (Log* l : logs)
	{ 
		l->updateLogs(dt);
	}
	frog->updateFrog(dt);

	if (frog->trans.position.y > m_units * 6)
	{
		checkCollCars();
	}
	else if (frog->trans.position.y < m_units * 7.0f)
	{
		if (frog->trans.position.y < m_units * 2)
		{ 
			playing = false; 
			frog->~Frog();
		}
		checkCollLogs();
	}
	return playing;
}

void Game::Render(RenderManager& renderManager)
{
	renderManager.Render(bgSprite, bgTrans);
	for (Car* c : cars)
	{ 
		c->renderCars(renderManager);
	}
	for (Log* l : logs)
	{ 
		l->renderLogs(renderManager);
	}
	for (Health* h : playerHealth) 
	{ 
		renderManager.Render(h->sprites, h->trans);
	}
	frog->renderFrog(renderManager);
}

void Game::checkCollCars()
{
	for (Car* c : cars)
	{
		if (CollisionManager::CheckCollision(c->coll, frog->coll))
		{
			frog->trans.position.x = 0;
			frog->trans.position.y = m_units * 13;
			frog->m_moving = false;
			frog->coll.SetPosition((int)(frog->trans.position.x + m_units / 4.0f), (int)(frog->trans.position.y + m_units / 4.0f));
			frog->currSprite = frog->sit;
			playerHealth.pop_back();
			if (playerHealth.size() == 0)
			{
				playing = false;
				frog->~Frog();
			}
		}
	}
}

void Game::checkCollLogs() 
{
	bool moveFrog = false;
	float frogSpeed = 0;
	for (Log* l : logs)
	{
		if (CollisionManager::CheckCollision(l->coll, frog->coll) && frog->m_moving == false)
		{
			frogSpeed = l->m_speed * l->m_speed2;
			moveFrog = true;
		}
	}
	if (moveFrog)
	{
		frog->trans.position.x += frogSpeed;
		frog->coll.SetPosition((int)(frog->trans.position.x + m_units / 4.0f), (int)(frog->trans.position.y + m_units / 4.0f));
	}
	else if (frog->m_dx == 0 && frog->m_dy == 0)
	{
		frog->trans.position.x = 0;
		frog->trans.position.y = m_units * 13;
		frog->m_moving = false;
		frog->coll.SetPosition((int)(frog->trans.position.x + m_units / 4.0f), (int)(frog->trans.position.y + m_units / 4.0f));
		frog->currSprite = frog->sit;
		playerHealth.pop_back();
		if (playerHealth.size() == 0)
		{
			playing = false;
			frog->~Frog();
		}
	}
}

void Game::loadCars()
{
	cars[10]->pushCar(-6, 5, 5, true);
	cars[11]->pushCar(-6, 5, 5 + 5, true);

	cars[9]->pushCar(4, 4, 4, false);

	cars[6]->pushCar(-4, 3, 3, false);
	cars[7]->pushCar(-4, 3, 3 + 4, false);
	cars[8]->pushCar(-4, 3, 3 + 12, false);

	cars[3]->pushCar(2, 2, 2, false);
	cars[4]->pushCar(2, 2, 2 + 4, false);
	cars[5]->pushCar(2, 2, 2 + 7, false);

	cars[0]->pushCar(-2, 1, 1, false);
	cars[1]->pushCar(-2, 1, 1 + 4, false);
	cars[2]->pushCar(-2, 1, 1 + 10, false);
}

void Game::loadLogs()
{
	logs[0]->pushLog(4, 5, 0, 5);
	logs[1]->pushLog(4, 5, 6, 5);
	logs[2]->pushLog(4, 5, 12, 5);

	logs[3]->pushLog(-4, 4, -3, 3);
	logs[4]->pushLog(-4, 4, 1, 3);
	logs[5]->pushLog(-4, 4, 5, 3);
	logs[6]->pushLog(-4, 4, 9, 3);

	logs[7]->pushLog(8, 3, 0, 6);
	logs[8]->pushLog(8, 3, 10, 6);

	logs[9]->pushLog(1, 2, 0, 4);
	logs[10]->pushLog(1, 2, 0 + 6, 4);
	logs[11]->pushLog(1, 2, 0 + 12, 4);

	logs[12]->pushLog(-6, 1, 0, 3);
	logs[13]->pushLog(-6, 1, 0 + 4, 3);
	logs[14]->pushLog(-6, 1, 0 + 8, 3);
	logs[15]->pushLog(-6, 1, 0 + 12, 3);
}

void Game::OnKeyDown(KeyCode key)
{
	frog->OnKeyDown(key);
}

void Game::OnKeyUp(KeyCode key)
{}