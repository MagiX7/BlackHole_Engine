#pragma once

#include "Module.h"
#include "Asteroid.h"
#include "p2List.h"

class SDL_Texture;

class AsteroidManager : public Module
{
public:
	AsteroidManager(App* parent, bool startEnabled = true);
	~AsteroidManager();

	bool Start() override;
	update_status Update(float dt) override;
	void Draw();
	bool CleanUp() override;

	Asteroid* CreateAsteroid(int radius, bhVec2 position);
	void DestroyAsteroid(Asteroid* ast);

	bool CheckCollision(bhBody* body);
	
public:

	p2List<Asteroid*> asteroidList;

	SDL_Texture* texture;
};