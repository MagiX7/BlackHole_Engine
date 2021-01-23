#pragma once

#include "Scene.h"
#include "Animation.h"

class Input;
enum class update_status;

class SDL_Texture;

class SceneDead : public Scene
{
public: 
	SceneDead();
	virtual ~SceneDead();

	bool Load(Texture* tex) override;
	update_status Update(Input* input, float dt) override;
	update_status Draw(Render* ren) override;
	bool UnLoad(Texture* tex);

private:

	SDL_Texture* bg;
	SDL_Texture* textureFire;

	Animation animFire;
};