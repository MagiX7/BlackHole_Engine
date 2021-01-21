#pragma once

#include "bhBody.h"
#include "Animation.h"
#include "Scene.h"

struct SDL_Texture;

class AsteroidManager;
class AstronautManager;
class SceneGameplay;

class Spaceship
{
public:
	Spaceship(App* app, SceneGameplay* gameplay);
	~Spaceship();

	bool Start();
	update_status PreUpdate();
	update_status Update(float dt, AsteroidManager* asteroid, AstronautManager* astronaut);
	void Draw();
	bool CleanUp();

	inline bhBody* GetBody()
	{
		return body;
	}

	void AddHealth(float h) { health += h; }
	void AddFuel(float f) { fuel += f; }
	void AddAmmo(int a) { ammo += a; }
	void LaunchMissile();
	void AddScore();

	void HandleInput(float dt);
	void Dead();
public:
	float health = 100.0f;
	float fuel = 0.0f;
	int ammo = 3;
	int astronautsCollected = 0;

private:
	
	SDL_Texture* texture;

	Animation* currentAnim;
	Animation idleAnim;
	Animation flyAnim;
	Animation engineOnAnim;
	Animation explosionAnim;

	bhBody* body;
	bhBody* missile;

	int fontsIndex;

	// Score
	char scoreAstronautsText[3] = { "\0" };
	int scoreFx = 0;
	SDL_Texture* scoreTexture;

	char fuelText[3] = { "\0" };

	App* app;
	SceneGameplay* scene;


	int astronautFx;
};