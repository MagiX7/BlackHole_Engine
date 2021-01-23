#pragma once

#include "Module.h"
#include "Scene.h"
#include "Astronaut.h"

class bhBody;
class Spaceship;
class AstronautManager;
class AsteroidManager;

struct SDL_Texture;

class SceneGameplay : public Scene
{
public:
	SceneGameplay(App* parent);
	virtual ~SceneGameplay();

	bool Load(Texture* tex) override;
	update_status Update(Input* input, float dt) override;
	update_status Draw(Render* ren) override;
	bool Unload(Texture* tex) override;


public:
	bhBody* earth;
	bhBody* moon;

	Spaceship* spaceship;
	bool relaunchSpaceship = false;

	SDL_Texture* bgTop;
	SDL_Texture* bgBottom;
	App* app;
	AsteroidManager* asteroidManager;
	AstronautManager* astronautManager;

	int waterDropFx;
	bool waterDropPlayOnce;
	bool arriveMoon;
};