#pragma once

#include "Module.h"

class Scene : public Module
{
public:
	Scene(App* parent, bool startEnabled = true);
	~Scene();

	bool Start() override;
	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;

};
