#pragma once

#include <math.h>
#include "bhBody.h"
#include "bhVec2.h"

class SDL_Texture;

class Astronaut
{
public:

	Astronaut();
	~Astronaut();

	bool Start();
	bool Update(float dt);
	void Draw();
	bool CleanUp();

	inline bhBody* GetBody()
	{
		return body;
	}

	
	void SetBody(bhBody* body);
	void SetInitialPos(bhVec2 initialPos);
	SDL_Texture* texture;

private:

	bhBody* body;

	bhVec2 initialPos;

	float speedY;
	float speedX;

};