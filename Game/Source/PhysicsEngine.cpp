#include "App.h"
#include "Spaceship.h"

#include "PhysicsEngine.h"
#include <math.h>

PhysicsEngine::PhysicsEngine()
{
	aeroDrag = 0.01f;
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

void PhysicsEngine::ForceGravity(bhBody& body1)
{
	float gravity = 0.0f;

	if (body1.GetPosition().y > PIXEL_TO_METERS(-5000) && body1.GetPosition().y <= PIXEL_TO_METERS(250))
	{
		//LOG("ON FIRST IF=====================");
		gravity = 10.0f;
		float b = gravity;
		float m = (gravity) / PIXEL_TO_METERS(5000);
		float forceGravity = m * body1.GetPosition().y + b;
		bhVec2 drag = AeroDrag(&body1);

		body1.AddForce(bhVec2(drag));
		body1.AddForce(bhVec2(0, forceGravity));

		LOG("FORCE GRAVITY %f", forceGravity);
		LOG("DRAG FORCE %f", drag.y);
	}
	else if (body1.GetPosition().y < PIXEL_TO_METERS(-5001) && body1.GetPosition().y >= PIXEL_TO_METERS(-9000))
	{
		//LOG("ON SECOND IF===================")
		gravity = 0.0f;
		float b = gravity;
		float m = (gravity) / PIXEL_TO_METERS(9000);
		float forceGravity = m * body1.GetPosition().y + b;

		body1.AddForce(bhVec2(0, forceGravity));
		LOG("%f", forceGravity);
	}
	else if (body1.GetPosition().y < PIXEL_TO_METERS(-9001) && body1.GetPosition().y >= PIXEL_TO_METERS(-13000))
	{
		//LOG("ON THIRD IF=====================")
		gravity = -7.08f;
		float b = gravity;
		float m = (gravity) / PIXEL_TO_METERS(9000-13000);
		float forceGravity = m * body1.GetPosition().y + b;

		// TODO 
		//en principi la lluna no te atmosfera
		bhVec2 drag = AeroDrag(&body1);
		body1.AddForce(bhVec2(0, forceGravity + drag.y));
		LOG("%f", forceGravity);
	}
	else
	{
		//LOG("NO IF==========================")
	}
}

bhVec2 PhysicsEngine::Gravity()
{
	return gravity;
}

bhVec2 PhysicsEngine::AeroDrag(bhBody* b)
{
	bhVec2 dragVec = {};
	if (b->GetPosition().y < PIXEL_TO_METERS(-800))
	{
		// Drag coefficient
		float dragCoef = 7.0f;

		// Area affected
		float area = M_PI * b->GetBodyRadius() * b->GetBodyRadius() / 2;

		// Density of the fluid
		float airDensity = 2.5f;

		// Current velocity of the object
		float velocity = b->GetLinearVelocity().GetNorm();

		// Calculate drag force
		float forceDrag = dragCoef * area * (airDensity * (velocity * velocity)) / 2;

		bhVec2 direction = b->GetLinearVelocity().Normalize().Negate();

		bhVec2 dragVec = direction * forceDrag;
	}

	return dragVec;
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
	bhVec2 hydroBuoyForce = { 0,0 };

	bhVec2 waterLevel = { 0,PIXEL_TO_METERS(-800) };

	if (b->GetPosition().y >= waterLevel.y)
	{
		float angle = 0.0f;

		if ((b->GetPosition().y - waterLevel.y) > b->GetBodyRadius())
		{
			angle = 360.0f * M_PI / 180;
		}
		else
		{
			angle = 2 * acos((b->GetPosition().y - b->GetBodyRadius() - waterLevel.y) / b->GetBodyRadius());
		}

		LOG("Cantidad sumergida %f", (angle * 180 / M_PI));

		if (angle >= 360.0f * M_PI / 180)
		{
	
			float areaSummerged = ((pow(b->GetBodyRadius(), 2.0f) / 2) * (angle - sin(angle)));

			float pression = (b->GetPosition().y - waterLevel.y) * 2.5f;

			float Fpression = pression * areaSummerged / 2;

			bhVec2 direction = bhVec2(0, waterLevel.y - b->GetPosition().y).Normalize();

			float density = 3.0f;
			float gravity = 10.0f;

			float forceBuoyancy = density * 10.0f * areaSummerged;
			hydroBuoyForce = direction * forceBuoyancy;

			bhVec2 fPression = direction * Fpression;

			b->AddForce(fPression);
			b->AddForce(hydroBuoyForce);
			bhVec2 dragForce = HydroDrag(b);
			b->AddForce(dragForce);

			LOG("PRESSION %f  %f", fPression.x, fPression.y);
			LOG("HYDROFORCE %f  %f", hydroBuoyForce.x, hydroBuoyForce.y);
			LOG("DRAG HYDRO %f  %f", dragForce.x, dragForce.y);

		}
		else
		{
			float areaSummerged = ((pow(b->GetBodyRadius(), 2.0f) / 2) * (angle - sin(angle)));

			bhVec2 direction = b->GetLinearVelocity().Normalize().Negate();

			float density = 3.0f;

			float forceBuoyancy = density * 10.0f * areaSummerged;
			hydroBuoyForce = direction * forceBuoyancy;
			b->AddForce(hydroBuoyForce);
			bhVec2 dragForce = HydroDrag(b);
			b->AddForce(dragForce);
		}
	}

	return hydroBuoyForce;
}

bhVec2 PhysicsEngine::HydroDrag(bhBody* b)
{
	bhVec2 hydroDragForce;

	// Velocity friction coefficient
	float velocityCoef = 15.0f;

	// Current velocity of the object
	float velocity = b->GetLinearVelocity().GetNorm();

	// Calculate drag force
	float forceDrag = velocityCoef * velocity;
	
	// We get the direction of the body itself (Negate it, because drag always goes backwards from the velocity)
	bhVec2 direction = b->GetLinearVelocity().Normalize().Negate();

	// Multiply the force itself to the direction already calculated in the linea bove
	bhVec2 dragVec = direction * forceDrag;

	return dragVec;
}

void PhysicsEngine::Step(float dt)
{
	p2List_item<bhBody*>* item = bodyList.getFirst();
	while (item != nullptr)
	{
		if (item->data->type == BodyType::DYNAMIC && item->data->IsActive())
		{
			item->data->SetAcceleration(bhVec2(0,0));
			item->data->ResetForce();
			ForceGravity(*item->data);
			HydroBuoy(item->data);
			item->data->ApplyNewtonSecondLaw();
			Integrator(item->data->GetPosition(), item->data->GetLinearVelocity(), item->data->GetAcceleration(), dt);
		}
		else if(item->data->type == BodyType::NO_GRAVITY && item->data->IsActive())
			Integrator(item->data->GetPosition(), item->data->GetLinearVelocity(), item->data->GetAcceleration(), dt);
		else if (item->data->type == BodyType::SENSOR && item->data->IsActive())
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

	if (b2->type != BodyType::SENSOR)
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