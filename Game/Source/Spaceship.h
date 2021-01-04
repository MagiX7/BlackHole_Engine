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
	void LaunchMissile()
	{
		bhBody* missile;
		missile->SetPosition(this->body->GetPosition());
		missile->SetLinearVelocity(bhVec2(this->body->GetLinearVelocity().x * 1.5f, this->body->GetLinearVelocity().y * 1.5f ));
	}


public:
	float health;
	float fuel;
	int ammo = 3;

private:
	
	SDL_Texture* texture;
	Animation* currentAnim;
	Animation idleAnim;
	Animation flyAnim;
	Animation engineOnAnim;

	bhBody* body;

};

