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

	SDL_Texture* const Load(const char* path);
	void Unload(SDL_Texture* texture);

public:
	p2List<SDL_Texture*> textures;
};