#include "App.h"
#include "Spaceship.h"

#include "PhysicsEngine.h"
#include <math.h>

PhysicsEngine::PhysicsEngine()
{
	gravity = bhVec2(PIXEL_TO_METERS(0), PIXEL_TO_METERS(100));
	aeroDrag = 0.3f;
	aeroLift = 0.3f;
	hydroDrag = 0.3f;
}

PhysicsEngine::~PhysicsEngine()
{
}

bhVec2 PhysicsEngine::ForceGravity(float gravity, float mass1, float mass2, float distance, bhVec2 direction)
{
	bhVec2 forceGravity;

	float gravityFormule = (gravity * (mass1 * mass2) / (distance * distance));

	forceGravity.x = direction.x * gravityFormule;
	forceGravity.y = direction.y * gravityFormule;

	return forceGravity;
}

bhVec2 PhysicsEngine::ForceGravity(bhBody& body1)
{
	/*bhVec2 forceGravity;

	bhVec2 distance = {};
	distance = body2.GetPosition() - body1.GetPosition();
	float distanceMod = sqrt((distance.x*distance.x) + (distance.y*distance.y));
	
	
	float gravityFormule = (gravity * (body1.GetBodyMass() * body2.GetBodyMass()) / (distanceMod * distanceMod));
	
	forceGravity.x = direction.x * gravityFormule;
	forceGravity.y = direction.y * gravityFormule;*/
	float gravity1 = 5.0f;
	float gravity2 = 0.0f;
	float gravity3 = -2.0f;
	LOG(" NAVE POS X %f POS Y %f ", body1.GetPosition().x, body1.GetPosition().y);
	if (body1.GetPosition().y < PIXEL_TO_METERS(-5000) && body1.GetPosition().y >= PIXEL_TO_METERS(0))
	{

		float b = gravity1;
		float m = (-gravity1) / PIXEL_TO_METERS(5000);
		float forceGravity = m * body1.GetPosition().y + b;

		body1.AddForce(bhVec2(0, forceGravity));
	}

	return bhVec2(1.0f,2.0f);
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
	p2List_item<bhBody*>* item = bodyList.getFirst();
	while (item != nullptr)
	{
		if (item->data->type == BodyType::DYNAMIC && item->data->IsActive())
		{
			ForceGravity(*item->data);
			Integrator(item->data->GetPosition(), item->data->GetLinearVelocity(), item->data->GetAcceleration() /*+ gravity*/, dt);
		}

		else if(item->data->type == BodyType::NO_GRAVITY && item->data->IsActive())
			Integrator(item->data->GetPosition(), item->data->GetLinearVelocity(), item->data->GetAcceleration(), dt);

		item = item->next;
	}

	/*else if (app->spaceship->GetBody()->GetPosition().y <= 0)
		gravity.y = 9.81f - ((app->scene->floor->GetPosition().y - app->spaceship->GetBody()->GetPosition().y) / 9.81f);*/

	//LOG("gravity = %f", gravity.y);

	for (p2List_item<bhBody*>* item = bodyList.getFirst(); item != nullptr; item = item->next)
	{
		for (p2List_item<bhBody*>* item2 = item->next; item2 != nullptr; item2 = item2->next)
		{
			if (Intersection(item->data, item2->data) && item->data->IsActive())
			{
				Collisions(item->data, item2->data);
			}
		}
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
	
	// First we get the normal corresponding from the world to the body
	bhVec2 dir = b->GetPosition() - b2->GetPosition();
	bhVec2 dirNoNormalized = dir;

	// We normalize the vector, since we only want the direction
	dir = dir.Normalize();
	
	// We get the actual velocity of the spaceship
	bhVec2 newSpeed = b->GetLinearVelocity();

	// We get the speed as a float
	float speed = sqrt((newSpeed.x * newSpeed.x) + (newSpeed.y * newSpeed.y));

	// We now multiply the speed for the direction so the spaceship knows the direction where it has to go to
	newSpeed = dir * speed;

	if (b2->GetName() == "floor")
		newSpeed = newSpeed * 0.6f;
	
	else
		newSpeed = newSpeed * 0.9f;

	b->SetLinearVelocity(newSpeed);
}

void PhysicsEngine::AddBody(bhBody* b)
{
	bodyList.add(b);
}

void PhysicsEngine::DeleteBody(bhBody* b)
{
	p2List_item<bhBody*>* item = bodyList.getFirst();

	while (item != nullptr)
	{
		if (item->data == b)
		{
			bodyList.del(item);
		}

		item = item->next;
	}
}

void PhysicsEngine::Integrator(bhVec2& pos, bhVec2& v, bhVec2& a, float dt)
{

	// Velocity-Verlet
	pos.x += v.x * dt + 0.5 * a.x * dt * dt;
	pos.y += v.y * dt + 0.5 * a.y * dt * dt;

	v.x += a.x * dt;
	v.y += a.y * dt;

}