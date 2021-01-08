#pragma once

#include "bhBody.h"
#include "Animation.h"

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

	void AddHealth(float h) { health += h; }
	void AddFuel(float f) { fuel += f; }
	void AddAmmo(int a) { ammo += a; }
	void LaunchMissile();
	void AddScore();


public:
	float health = 0.0f;
	float fuel = 0.0f;
	int ammo = 3;
	int astronautsCollected = 0;

private:
	
	SDL_Texture* texture;
	Animation* currentAnim;
	Animation idleAnim;
	Animation flyAnim;
	Animation engineOnAnim;

	bhBody* body;
	bhBody* missile;

	int fontsIndex;

	// Score
	char scoreAstronautsText[3] = { "\0" };

	int scoreFx = 0;

};