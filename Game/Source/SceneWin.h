#pragma once

#include "Scene.h"
#include "Animation.h"

class Input;
enum class update_status;

class SDL_Texture;

class SceneWin : public Scene
{
public:
	SceneWin();
	virtual ~SceneWin();

	bool Load(Texture* tex) override;
	update_status Update(Input* input, float dt) override;
	update_status Draw(Render* ren) override;
	bool Unload(Texture* tex) override;

private:

	SDL_Texture* bg;
};