#pragma once

#include <math.h>
#include "bhBody.h"
#include "bhVec2.h"

class SDL_Texture;

class Asteroid
{
public:
	Asteroid();
	~Asteroid();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	inline bhBody* GetBody()
	{
		return body;
	}

	void SetBody(bhBody* body);

	SDL_Texture* texture;

private:

	bhBody* body;
};