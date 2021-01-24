#pragma once

#include <math.h>
#include "bhBody.h"
#include "bhVec2.h"
#include "Animation.h"

class Animation;
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

	Animation dieAnim;

	bool die;
private:

	bhBody* body;
};