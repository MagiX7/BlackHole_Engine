#include "Physics.h"

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
}

float PhysicsEngine::Gravity()
{
	return -9.8f;
}

float PhysicsEngine::AeroDrag()
{
	return 0.0f;
}

float PhysicsEngine::AeroLift()
{
	return 0.0f;
}

float PhysicsEngine::HydroBuoy()
{
	return 0.0f;
}

float PhysicsEngine::HydroDrag()
{
	return 0.0f;
}

void PhysicsEngine::Step(float dt)
{
}

void PhysicsEngine::Collisions()
{
}
