#pragma once

#include "Module.h"
#include "Astronaut.h"
#include "bhBody.h"
#include "bhVec2.h"

#include "p2List.h"

class SDL_Texture;

class AstronautManager
{
public:
	AstronautManager();
	~AstronautManager(){}

	bool Start();
	bool Update(float dt);
	bool CleanUp(Texture* tex);
	void Draw(Render* ren);

	Astronaut* CreateAstronaut(int radius, bhVec2 initialPos, Physics* physics);
	void DeleteAstronaut(Astronaut* astronaut, Physics* physics);
	void DeleteAstronaut(bhBody* astronaut, Physics* physics);
	void SetTexture(Texture* tex);
	bool CheckCollision(bhBody* body, Physics* physics);
	bool CheckCollision(SDL_Rect rect, Physics* physics);

	p2List<Astronaut*> astronautsList;

private:

	SDL_Texture* astronautTexture;

};