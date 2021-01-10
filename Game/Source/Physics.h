#pragma once

#include "Module.h"

#include "bhBody.h"
#include "PhysicsEngine.h"

class Physics : public Module
{
public:

	Physics(App* app, bool start_enabled = true);
	~Physics();

	bool Start() override;

	update_status PreUpdate() override;
	update_status Update(float dt) override;
	update_status PostUpdate() override;

	bool CleanUp() override;

	bhBody* CreateBody(SString n, BodyType type);
	void DestroyBody(bhBody* b);

	inline PhysicsEngine* GetWorld() { return world; }

private:

	p2List<bhBody*> bodies;

	PhysicsEngine* world;

};