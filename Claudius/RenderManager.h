#pragma once

#include <vector>

struct Sprite;
struct Transform;
struct Rectangle;
struct Color;

struct RenderManager
{
	// Sprite and Rect entries are used by the RenderManager to gather everything to be rendered
	// before actually rendering them. These are references which means if adresses to local variables
	// are being sent to the RenderManager they will not be rendered correctly since those temporary
	// variables will most likely be deallocated between the queueing the rendering to actually rendering.
	struct SpriteEntry
	{
		const Sprite &sprite;
		const Transform& trans;
	};

	struct RectEntry
	{
		const Rectangle& rect;
		const Color& color;
	};

	// renders a sprite on a specific transform
	void Render(const Sprite& sprite, const Transform& trans);

	// renders a rectangle of a color
	void Render(const Rectangle& rect, const Color& color);
	void Clear();

	std::vector<SpriteEntry> spriteEntries;
	std::vector<RectEntry> rectEntries;
};
