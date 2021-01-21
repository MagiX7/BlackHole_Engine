#pragma once

#include "Globals.h"

enum class SceneType
{
	INTRO,
	GAMEPLAY,
	ENDING
};

class Texture;
class Render;
class Input;

class SDL_Texture;

class Scene
{
public:
	Scene() {}

	// Destructor
	virtual ~Scene() {};

	// Called before the first frame
	virtual bool Load(Texture* tex, SDL_Texture* bg) { return true; }

	// Called each loop iteration
	virtual update_status Update(Input* input, float dt) { return update_status::UPDATE_CONTINUE; }

	// Called before all updates
	virtual update_status Draw(Render* ren) { return update_status::UPDATE_CONTINUE; }

	// Called before quitting
	virtual bool Unload(Texture* tex) { return true; }

	void TransitionToScene(SceneType scene)
	{
		transitionRequired = true;
		nextScene = scene;
	}

public:
	bool active = false;

	bool transitionRequired = false;
	SceneType nextScene;
};