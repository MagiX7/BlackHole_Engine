#pragma once

#include "bhBody.h"

class SDL_Texture;

class Spaceship : public bhBody, public Module
{
public:
	Spaceship(App* app, bool start_enabled = true);
	~Spaceship();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	void Draw();
	bool CleanUp();


public:
	float health;
	float fuel;

private:
	
	SDL_Texture* texture;
	
	float r; // for collision detection


};

