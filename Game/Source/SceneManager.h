#pragma once

#include "Module.h"
#include "Scene.h"

class SceneManager : public Module
{
public:
	SceneManager(App* parent, bool startEnabled = true);
	~SceneManager();

	bool Start() override;
	update_status Update(float dt) override;
	update_status PostUpdate() override;
	bool CleanUp() override;

private:
	Scene* current;
	Scene* next;

	bool onTransition;
	bool fadeOutCompleted;
	float transitionAlpha;

	SDL_Texture* texture;
};