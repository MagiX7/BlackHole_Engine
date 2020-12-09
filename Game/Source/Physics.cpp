#include "App.h"
#include "Spaceship.h"

#include "Physics.h"

PhysicsEngine::PhysicsEngine(App* app, bool start_enabled) : Module(app, start_enabled)
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
	Integrator(app->spaceship->GetPosition().x, app->spaceship->GetPosition().y, app->spaceship->GetAcceleration().x, dt);

}

void PhysicsEngine::Collisions()
{
}

void PhysicsEngine::Integrator(float& x, float& v, float a, float dt)
{
	// Velocity-Verlet
	x += v * dt + 0.5 * a * dt * dt;
	v += a * dt;
}
