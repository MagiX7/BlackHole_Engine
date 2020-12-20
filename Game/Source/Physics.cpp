#include "App.h"
#include "Spaceship.h"

#include "Physics.h"
#include <math.h>

PhysicsEngine::PhysicsEngine(App* app, bool start_enabled) : Module(app, start_enabled)
{
	gravity = bhVec2(PIXEL_TO_METERS(0), PIXEL_TO_METERS(250));
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
	Integrator(app->spaceship->GetBody()->GetPosition(), app->spaceship->GetBody()->GetLinearVelocity(), app->spaceship->GetBody()->GetAcceleration() + gravity, dt);

	p2List_item<bhBody*>* item = bodyList.getFirst();
	while (item != nullptr)
	{
		if (item->data->GetName() != "spaceship")
		{
			if (Intersection(app->spaceship->GetBody(), item->data))
			{
				Collisions(app->spaceship->GetBody(), item->data);
			}
		}
		item = item->next;
	}
}

bool PhysicsEngine::Intersection(bhBody* b1, bhBody* b2)
{
	float x = b2->GetPosition().x - (b1->GetPosition().x);
	float y = b2->GetPosition().y - (b1->GetPosition().y);
	float dist = sqrt(pow(x, 2) + pow(y, 2));

	if (dist < b1->GetBodyRadius() + b2->GetBodyRadius())
		return true;
	else
		return false;
}

void PhysicsEngine::Collisions(bhBody* b, bhBody* b2)
{
	bhVec2 dir = b2->GetPosition() - b->GetPosition();
	dir = dir.Normalize();

	bhVec2 impact = dir + b->GetBodyRadius();

	bhVec2 newSpeed = impact * b->GetLinearVelocity();
	
	b->SetLinearVelocity(newSpeed.Negate());

	// =======================================================================================================================




	/*float dist = sqrt(pow(b2->GetPosition().x - b->GetPosition().x, 2) + pow(b2->GetPosition().y - b->GetPosition().y, 2));

	float intersection = b2->GetBodyRadius() - b->GetBodyRadius();

	bhVec2 groundNormal = b2->GetPosition() + intersection;
	groundNormal = groundNormal.Normalize();

	bhVec2 newSpeed = b->GetLinearVelocity() * groundNormal;
	b->SetLinearVelocity(newSpeed);*/

	// =======================================================================================================================

	/*float y = b->GetPosition().y + (b->GetBodyRadius());

	if (y > (b2->GetPosition().y - b2->GetBodyRadius()) && b2->GetName() == "floor")
	{
		bhVec2 aux = bhVec2(b->GetLinearVelocity().x, b->GetLinearVelocity().Negate().y * 0.9f);
		b->SetLinearVelocity(aux);
	}

	else if ((b->GetPosition().y - b->GetBodyRadius()) < b2->GetPosition().y + PIXEL_TO_METERS(50) && b2->GetName() == "top")
	{
		bhVec2 aux = bhVec2(b->GetLinearVelocity().x, b->GetLinearVelocity().Negate().y * 0.9f);
		b->SetLinearVelocity(aux);
	}*/
	
	/*float y = b->GetPosition().y + (b->GetBodyRadius());

	if (y > (b2->GetPosition().y - b2->GetBodyRadius()) && b2->GetName() == "floor")
	{
		bhVec2 aux = bhVec2(b->GetLinearVelocity().x, b->GetLinearVelocity().Negate().y * 0.9f);
		b->SetLinearVelocity(aux);
	}

	else if ((b->GetPosition().y - b->GetBodyRadius()) < b2->GetPosition().y + PIXEL_TO_METERS(50) && b2->GetName() == "top")
	{
		bhVec2 aux = bhVec2(b->GetLinearVelocity().x, b->GetLinearVelocity().Negate().y * 0.9f);
		b->SetLinearVelocity(aux);
	}*/
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

bhBody* PhysicsEngine::CreateBody(SString n)
{
	bhBody* b = new bhBody(n);

	bodyList.add(b);

	return b;
}

void PhysicsEngine::DestroyBody(bhBody* b)
{
	p2List_item<bhBody*>* item = bodyList.getFirst();

	while (item != nullptr)
	{
		if (item->data == b)
			bodyList.del(item);

		item = item->next;
	}
}