#pragma once

#include "Module.h"
#include "Scenes.h"
#include "Astronaut.h"

class bhBody;
class Spaceship;
class AstronautManager;
class AsteroidManager;

struct SDL_Texture;

class Scene : public Scenes
{
public:
	Scene(App* parent);
	virtual ~Scene();

	bool Load(Texture* tex, SDL_Texture* bg) override;
	update_status Update(Input* input, float dt) override;
	update_status Draw(Render* ren) override;
	bool Unload(Texture* tex) override;


public:
	bhBody* earth;
	bhBody* moon;

	Spaceship* spaceship;

	SDL_Texture* bg;
	App* app;
	AsteroidManager* asteroidManager;
	AstronautManager* astronautManager;
};