#include "App.h"
#include "Spaceship.h"

#include "Physics.h"
#include <math.h>

PhysicsEngine::PhysicsEngine(App* app, bool start_enabled) : Module(app, start_enabled)
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
		if(item->data->type == BodyType::DYNAMIC)
			Integrator(item->data->GetPosition(), item->data->GetLinearVelocity(), item->data->GetAcceleration() + gravity, dt);

		else if(item->data->type == BodyType::NO_GRAVITY)
			Integrator(item->data->GetPosition(), item->data->GetLinearVelocity(), item->data->GetAcceleration(), dt);

		item = item->next;
	}

	/*else if (app->spaceship->GetBody()->GetPosition().y <= 0)
		gravity.y = 9.81f - ((app->scene->floor->GetPosition().y - app->spaceship->GetBody()->GetPosition().y) / 9.81f);*/

	LOG("gravity = %f", gravity.y);

	item = bodyList.getFirst();
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
	/*bhVec2 dir = b2->GetPosition() - b->GetPosition();
	dir = dir.Normalize();

	bhVec2 impact = dir + b->GetBodyRadius();

	bhVec2 impac;
	impac.x = dir.x + b->GetBodyRadius();
	impac.y = dir.y + b->GetBodyRadius();


	bhVec2 newSpeed = impact * b->GetLinearVelocity();
	
	b->SetLinearVelocity(newSpeed.Negate());*/
	
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


	if (b2->GetName() == "astronaut")
	{
		app->astronautManager->DeleteAstronaut(b2);
		app->spaceship->AddScore();
	}
	else
	{
		b->SetLinearVelocity((newSpeed));
	}



	// =======================================================================================================================

	/*bhVec2 groundNormal = bhVec2(b2->GetPosition().x, b2->GetPosition().y + b2->GetBodyRadius());

	float grNormalModule = sqrt(groundNormal.x * groundNormal.x + groundNormal.y * groundNormal.y);
	float dirModule = sqrt(dirNoNormalized.x * dirNoNormalized.x + dirNoNormalized.y * dirNoNormalized.y);

	bhVec2 sinVec = dirNoNormalized - groundNormal;
	float sin = sqrt(sinVec.x * sinVec.x + sinVec.y * sinVec.y);

	float angle = atan2(sin, grNormalModule / dirModule);
	angle = angle * 180 / M_PI;*/

	// =======================================================================================================================


	/*bhVec2 groundNormal = bhVec2(b2->GetPosition().x, b2->GetPosition().y + b2->GetBodyRadius());
	float grNormalModule = sqrt(groundNormal.x * groundNormal.x + groundNormal.y * groundNormal.y);
	float dirModule = sqrt(dirNoNormalized.x * dirNoNormalized.x + dirNoNormalized.y * dirNoNormalized.y);
	
	float dot = dirNoNormalized.Dot(groundNormal);

	float c = dot / (grNormalModule * dirModule);
	float angle = acos(c);

	angle = angle * 180 / M_PI;
	
	

	int a = 0;
	a = 1;*/

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

	// Velocity-Verlet
	pos.x += v.x * dt + 0.5 * a.x * dt * dt;
	pos.y += v.y * dt + 0.5 * a.y * dt * dt;

	v.x += a.x * dt;
	v.y += a.y * dt;

}

bhBody* PhysicsEngine::CreateBody(SString n, BodyType type)
{
	bhBody* b = new bhBody(n, type);

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