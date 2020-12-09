#pragma once

#include "Module.h"

class PhysicsEngine : public Module
{
public:
	PhysicsEngine(App* app, bool start_enabled = true);
	~PhysicsEngine();

	float Gravity();
	float AeroDrag();
	float AeroLift();
	float HydroBuoy();
	float HydroDrag();

	void Step(float dt);

	void Collisions();

private:

	void Integrator(float& x, float& v, float a, float dt);

};