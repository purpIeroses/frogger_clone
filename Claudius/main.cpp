#include "SDL.h"
#include "SDL_image.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Sprite.h"
#include "Transform.h"
#include "Image.h"

#include <iostream>
#undef main

// ResourceManager 

struct ResourceImpl
{
	struct Texture
	{
		SDL_Texture* texture;
		int width;
		int height;

	};
	ResourceImpl(SDL_Renderer* renderer) : renderer(renderer) {};
	std::vector<std::pair<std::string, Texture>> textures;
	SDL_Renderer* renderer;
	SDL_Texture* GetTexture(unsigned int id)
	{
		if (id < textures.size())
			return textures[id].second.texture;
		else
			return nullptr;
	}
};

bool ResourceManager::LoadImageFromFile(Image& image, const std::string &filePath)
{
	auto it = impl.textures.begin();
	unsigned int index = 0;
	while (it != impl.textures.end())
	{
		if ((*it).first == filePath)
		{
			image.id = index;
			image.width = (*it).second.width;
			image.height = (*it).second.height;
			return true;
		}
		it++;
		index++;
	}
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface != nullptr)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(impl.renderer, surface);
		if (texture != nullptr)
		{
			impl.textures.push_back(std::pair<std::string, ResourceImpl::Texture>(filePath, { texture,surface->w,surface->h } ));
			image.id = static_cast<unsigned int>(impl.textures.size() - 1);
			image.width = surface->w;
			image.height = surface->h;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		const char* error = IMG_GetError();
		return false;
	}
	return false;
};

const char* ResourceManager::GetError() 
{ 
	return SDL_GetError();
}


// RenderManager

struct RenderImpl
{
	SDL_Renderer* renderer;

};

void RenderManager::Render(const Sprite& sprite, const Transform& trans)
{
	spriteEntries.push_back({ sprite, trans });
}

void RenderManager::Render(const Rectangle& rect, const Color& color)
{
	rectEntries.push_back({ rect, color });
}

void RenderManager::Clear()
{
	spriteEntries.clear();
	rectEntries.clear();
}

SDL_RendererFlip TranslateFlip(Sprite::Flip flip)
{
	switch (flip)
	{
	case Sprite::Flip::None: return SDL_RendererFlip::SDL_FLIP_NONE; break;
	case Sprite::Flip::Horizontal: return SDL_RendererFlip::SDL_FLIP_HORIZONTAL; break;
	case Sprite::Flip::Vertical: return SDL_RendererFlip::SDL_FLIP_VERTICAL; break;
	default: return SDL_RendererFlip::SDL_FLIP_NONE; break;
	}
}

KeyCode TranslateKeyCode(SDL_Keycode code)
{
	switch (code)
	{
	case SDLK_ESCAPE: return KeyCode::ESCAPE; break;
	case SDLK_SPACE: return KeyCode::SPACE; break;
	case SDLK_RETURN: return KeyCode::ENTER; break;
	case SDLK_RETURN2: return KeyCode::ENTER; break;
	case SDLK_a: return KeyCode::A; break;
	case SDLK_b: return KeyCode::B; break;
	case SDLK_c: return KeyCode::C; break;
	case SDLK_d: return KeyCode::D; break;
	case SDLK_e: return KeyCode::E; break;
	case SDLK_f: return KeyCode::F; break;
	case SDLK_g: return KeyCode::G; break;
	case SDLK_h: return KeyCode::H; break;
	case SDLK_i: return KeyCode::I; break;
	case SDLK_j: return KeyCode::J; break;
	case SDLK_k: return KeyCode::K; break;
	case SDLK_l: return KeyCode::L; break;
	case SDLK_m: return KeyCode::M; break;
	case SDLK_n: return KeyCode::N; break;
	case SDLK_o: return KeyCode::O; break;
	case SDLK_p: return KeyCode::P; break;
	case SDLK_q: return KeyCode::Q; break;
	case SDLK_r: return KeyCode::R; break;
	case SDLK_s: return KeyCode::S; break;
	case SDLK_t: return KeyCode::T; break;
	case SDLK_u: return KeyCode::U; break;
	case SDLK_v: return KeyCode::V; break;
	case SDLK_w: return KeyCode::W; break;
	case SDLK_x: return KeyCode::X; break;
	case SDLK_y: return KeyCode::Y; break;
	case SDLK_z: return KeyCode::Z; break;
	case SDLK_LEFT: return KeyCode::LEFT_ARROW; break;
	case SDLK_RIGHT: return KeyCode::RIGHT_ARROW; break;
	case SDLK_UP: return KeyCode::UP_ARROW; break;
	case SDLK_DOWN: return KeyCode::DOWN_ARROW; break;
	default: return KeyCode::INVALID; break;
	}
}

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	if (IMG_Init(IMG_InitFlags::IMG_INIT_PNG | IMG_InitFlags::IMG_INIT_JPG) == 0)
	{
		const char* error = IMG_GetError();
		return 0;
	}
	SDL_Window* window = SDL_CreateWindow("Base", 0, 0, 0, 0, SDL_WindowFlags::SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		const char* error = SDL_GetError();
		return 0;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		const char* error = SDL_GetError();
		return 0;
	}
	bool running = true;
	bool quit = false;
	RenderManager renderManager;
	ResourceImpl resourceImpl(renderer);
	ResourceManager resourceManager(resourceImpl);
	Game game(resourceManager);

	int width = 500;
	int height = 500;
	std::string title = "";
	game.Enter(width, height, title);
	SDL_SetWindowSize(window, width, height);
	SDL_SetWindowTitle(window, title.c_str());
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	unsigned int FPS = 60;
	unsigned int ticksPerFrame = 1000 / FPS;
	float dt = 0.16f;
	unsigned int processTick = 0;
	unsigned int previousTick = SDL_GetTicks();
	unsigned int delayTicks = 0;
	while (running && !quit)
	{
		unsigned int currentTick = SDL_GetTicks();
		unsigned int elapsedTicks = currentTick - previousTick;
		previousTick = currentTick;
		if (elapsedTicks < ticksPerFrame)
		{
			delayTicks = ticksPerFrame - elapsedTicks;
			SDL_Delay(delayTicks);
			dt = (elapsedTicks + delayTicks) * 0.001f;
		}
		else
			dt = elapsedTicks * 0.001f;

		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT: quit = true; break;
			case SDL_KEYDOWN: game.OnKeyDown(TranslateKeyCode(e.key.keysym.sym)); break;
			case SDL_KEYUP: game.OnKeyUp(TranslateKeyCode(e.key.keysym.sym)); break;
			}
		}
		
		running = game.Update(dt);
		game.Render(renderManager);

		SDL_SetRenderDrawColor(renderer,0,0,0,0);
		SDL_RenderClear(renderer);
		for (auto &&entry : renderManager.spriteEntries)
		{
			SDL_Rect src{ entry.sprite.source.x, entry.sprite.source.y, entry.sprite.source.w, entry.sprite.source.h };
			SDL_Rect dst{ static_cast<int>(entry.trans.position.x),
							static_cast<int>(entry.trans.position.y),
							static_cast<int>(entry.sprite.source.w * entry.trans.scale),
							static_cast<int>(entry.sprite.source.h * entry.trans.scale) };
			SDL_RenderCopyEx(renderer, resourceImpl.GetTexture(entry.sprite.image->id),
				&src, &dst, entry.trans.rotation, NULL, TranslateFlip(entry.sprite.flip));
		}
		for (auto&& entry : renderManager.rectEntries)
		{
			SDL_SetRenderDrawColor(renderer, entry.color.r, entry.color.g, entry.color.b, entry.color.a);
			SDL_Rect rect{ entry.rect.x,
						   entry.rect.y,
						   entry.rect.w,
						   entry.rect.h };
			
			SDL_RenderDrawRect(renderer, &rect);
		}
		SDL_RenderPresent(renderer);
		renderManager.Clear();
		processTick = (SDL_GetTicks() - currentTick);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}
