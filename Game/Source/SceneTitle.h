#pragma once

#include "Scene.h"

struct SDL_Texture;

class SceneTitle : public Scene
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	bool Load(Texture* tex) override;
	update_status Update(Input* input, float dt) override;
	update_status Draw(Render* ren) override;
	bool Unload(Texture* tex) override;

public:

	SDL_Texture* bg;
};