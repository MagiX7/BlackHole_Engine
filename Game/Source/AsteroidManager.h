#pragma once

#include "Module.h"
#include "Asteroid.h"
#include "p2List.h"

class SDL_Texture;
class Physics;

class AsteroidManager
{
public:
	AsteroidManager();
	~AsteroidManager();

	bool Start();
	bool Update(float dt);
	void Draw(Render* render);
	bool CleanUp(Texture* tex);

	Asteroid* CreateAsteroid(int radius, bhVec2 position, Physics* physics);
	void DestroyAsteroid(Asteroid* ast);
	void SetTexture(Texture* tex);

	bool CheckCollision(bhBody* body, Physics* physics);
	
public:

	p2List<Asteroid*> asteroidList;

	SDL_Texture* texture;
	App* app;
};