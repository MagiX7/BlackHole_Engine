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

	void Collisions(bhBody* b, bhBody* b2);

private:

	void Integrator(bhVec2& x, bhVec2& v, bhVec2& a, float dt);

	bhVec2 gravity;
	float aeroDrag;
	float aeroLift;
	float hydroBuoy;
	float hydroDrag;
};