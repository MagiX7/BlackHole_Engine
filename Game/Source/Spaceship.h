#pragma once

#include "bhBody.h"

class SDL_Texture;

class Spaceship : public Module
{
public:
	Spaceship(App* app, bool start_enabled = true);
	~Spaceship();

	bool Start();
	update_status PreUpdate();
	update_status Update(float dt);
	void Draw();
	bool CleanUp();

	inline bhBody* GetBody()
	{
		return body;
	}

public:
	float health;
	float fuel;

private:
	
	SDL_Texture* texture;
	
	float r; // for collision detection

	bhBody* body;
};

