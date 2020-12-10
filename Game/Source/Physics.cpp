#include "App.h"
#include "Spaceship.h"

#include "Physics.h"

PhysicsEngine::PhysicsEngine(App* app, bool start_enabled) : Module(app, start_enabled)
{
	gravity = bhVec2(0, 250.0f);
	aeroDrag = 0.3f;
	aeroLift = 0.3f;
	hydroDrag = 0.3f;
}

PhysicsEngine::~PhysicsEngine()
{
}

bhVec2 PhysicsEngine::Gravity()
{
	return gravity;
}

bhVec2 PhysicsEngine::AeroDrag(bhBody* b)
{
	float density = b->GetBodyMass() /*b->*/;

	bhVec2 dragForce;

	float x = aeroDrag /* Area*/ * ((density * (b->GetLinearVelocity().x * b->GetLinearVelocity().x)) / 2);
	float y = aeroDrag /* Area*/ * ((density * (b->GetLinearVelocity().y * b->GetLinearVelocity().y)) / 2);

	dragForce = bhVec2(x, y);

	return dragForce;
}

bhVec2 PhysicsEngine::AeroLift(bhBody* b)
{
	float density = b->GetBodyMass() /*volumen*/;

	bhVec2 liftForce;

	float x = (density * (b->GetLinearVelocity().x * b->GetLinearVelocity().x) / 2) * aeroLift; /*area*/
	float y = (density * (b->GetLinearVelocity().y * b->GetLinearVelocity().y) / 2) * aeroLift; /*area*/

	liftForce = bhVec2(x, y);

	return liftForce;
}

bhVec2 PhysicsEngine::HydroBuoy(bhBody* b)
{
	bhVec2 hydroBuoyForce;

	return hydroBuoyForce;
}

bhVec2 PhysicsEngine::HydroDrag(bhBody* b)
{
	float density = b->GetBodyMass() /*b->*/;

	bhVec2 hydroDragForce;

	float x = hydroDrag /* Area*/ * ((density * (b->GetLinearVelocity().x * b->GetLinearVelocity().x)) / 2);
	float y = hydroDrag /* Area*/ * ((density * (b->GetLinearVelocity().y * b->GetLinearVelocity().y)) / 2);

	hydroDragForce = bhVec2(x, y);

	return hydroDragForce;
}

void PhysicsEngine::Step(float dt)
{
	Integrator(app->spaceship->GetPosition(), app->spaceship->GetLinearVelocity(), app->spaceship->GetAcceleration() + gravity, dt);

}

void PhysicsEngine::Collisions(bhBody* b, bhBody* b2)
{
	float y = b->GetPosition().y + (2 * b->GetBodyRadius());

	if (y >= b2->GetPosition().y)
	{
		b->SetLinearVelocity(b->GetLinearVelocity().Negate());
	}
}

void PhysicsEngine::Integrator(bhVec2& pos, bhVec2& v, bhVec2& a, float dt)
{
	// Calculate the total acceleration
	//a.x -= gravity.x;
	//a.y -= gravity.y;

	// Velocity-Verlet
	pos.x += v.x * dt + 0.5 * a.x * dt * dt;
	pos.y += v.y * dt + 0.5 * a.y * dt * dt;

	v.x += a.x * dt;
	v.y += a.y * dt;

}
