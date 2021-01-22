#pragma once

#include "Module.h"

#include "bhBody.h"
#include "PhysicsEngine.h"


#define PI 3.14159265358979323846f
#define DEG2RAD (PI/180.0f)
#define RAD2DEG (180.0f/PI)

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