#pragma once
#include <string>
#include <vector>
#include "KeyCode.h"
#include "Image.h"
#include "Sprite.h"
#include "Transform.h"
#include "Car.h"
#include "Frog.h"
#include "Log.h"

struct RenderManager;
struct ResourceManager;

struct Health
{
	Sprite sprites;
	Transform trans;
};

class Game
{
	Image bg;
	Image sheet;
	Sprite bgSprite;
	Transform bgTrans;
	ResourceManager& m_resourceManager;

	public:
		Game(ResourceManager& resourceManager);
		~Game();
		bool Enter(int& width, int& height, std::string& title); // References sent to the game from the base to set the window size and name
		bool Update(float dt); // If Games update returns false the program will exit
		void Render(RenderManager& rendererManager);
		void OnKeyDown(KeyCode key);
		void OnKeyUp(KeyCode key);
		void loadCars();
		void loadLogs();
		void checkCollCars();
		void checkCollLogs();
		float m_units;
		float m_scale;
		float Width;
		float Height;
		bool playing;
		Frog* frog;
		std::vector<Car*> cars;
		std::vector<Log*> logs;
		std::vector<Health*> playerHealth;
};