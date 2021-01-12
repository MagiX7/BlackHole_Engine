#pragma once

#include "Module.h"
#include "Astronaut.h"

class bhBody;

class Scene : public Module
{
public:
	Scene(App* parent, bool startEnabled = true);
	~Scene();

	bool Start() override;
	update_status PreUpdate() override;
	update_status Update(float dt) override;
	update_status PostUpdate() override;
	bool CleanUp() override;


public:
	bhBody* floor;
	bhBody* floor2;

	SDL_Texture* bg;

};
