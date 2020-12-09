#pragma once

#include "Module.h"

class bhVec2;
class bhBody;

class PhysicsEngine : public Module
{
public:
	PhysicsEngine(App* app, bool start_enabled = true);
	~PhysicsEngine();

	bhVec2 Gravity();
	bhVec2 AeroDrag(bhBody* b);
	bhVec2 AeroLift(bhBody* b);
	bhVec2 HydroBuoy(bhBody* b);
	bhVec2 HydroDrag(bhBody* b);

	void Step(float dt);

	void Collisions();

private:

	void Integrator(float& x, float& v, float a, float dt);

	bhVec2 gravity;
	float aeroDrag;
	float aeroLift;
	float hydroBuoy;
	float hydroDrag;
};