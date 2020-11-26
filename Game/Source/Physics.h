#pragma once

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	float Gravity();
	float AeroDrag();
	float AeroLift();
	float HydroBuoy();
	float HydroDrag();

	void Step(float dt);

	void Collisions();
};