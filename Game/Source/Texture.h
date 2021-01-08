#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2List.h"
#include "SDL\include\SDL.h"

class Texture : public Module
{
public:
	Texture(App* app, bool start_enabled = true);
	~Texture();

	bool Init();
	bool CleanUp();

	// Load Texture
	SDL_Texture* const Load(const char* path);
	SDL_Texture* const LoadSurface(SDL_Surface* surface);
	bool UnLoad(SDL_Texture* texture);
	void GetSize(const SDL_Texture* texture, uint& width, uint& height) const;

public:

	p2List<SDL_Texture*> textures;
};