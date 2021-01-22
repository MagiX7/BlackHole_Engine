#pragma once

#include "Scene.h"

#include "bhBody.h"
#include "Animation.h"

#include "SDL/include/SDL_rect.h"

class SDL_Texture;

class AsteroidManager;
class AstronautManager;
class SceneGameplay;

struct Missile
{
	bhVec2 position = { 0,0 };
	bhVec2 direction = { 0,0 };
	int damage = 50;
	SDL_Rect collider = { (int)position.x,(int)position.y,5,5 };
};


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

	void AddHealth(float h);
	void AddFuel(float f);
	void AddAmmo(int a);

	float GetFuel();

	void CreateMissile();
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
	p2List<Missile*> missiles;

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