#include "App.h"
#include "Spaceship.h"

#include "PhysicsEngine.h"
#include <math.h>

PhysicsEngine::PhysicsEngine()
{
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

void PhysicsEngine::ForceGravity(bhBody* body1)
{
	float gravity = 0.0f;

	if (body1->GetPosition().y > PIXEL_TO_METERS(-5000) && body1->GetPosition().y <= PIXEL_TO_METERS(250))
	{
		//LOG("ON FIRST IF=====================");
		gravity = 10.0f;
		float b = gravity;
		float m = (gravity) / PIXEL_TO_METERS(5000);
		float forceGravity = m * body1->GetPosition().y + b;
		bhVec2 drag = bhVec2(0, 0);

		if (body1->GetPosition().y > PIXEL_TO_METERS(-3000))
		{
			drag = AeroDrag(body1);
			float n = drag.y;
			float m = (drag.y) / PIXEL_TO_METERS(3000);
			float dragForce = m * body1->GetPosition().y + n;
			drag.y = dragForce;
		}
		body1->AddForce(bhVec2(0, forceGravity + drag.y));

		//LOG("FORCE GRAVITY %f", forceGravity);
		//LOG("DRAG FORCE %f", drag.y);
	}
	//else if (body1.GetPosition().y < PIXEL_TO_METERS(-5001) && body1.GetPosition().y >= PIXEL_TO_METERS(-9000))
	//{
	//	//LOG("ON SECOND IF===================")
	//	gravity = 0.0f;
	//	float b = gravity;
	//	float m = (gravity) / PIXEL_TO_METERS(9000);
	//	float forceGravity = m * body1.GetPosition().y + b;

	//	body1.AddForce(bhVec2(0, forceGravity));
	//	//LOG("%f", forceGravity);
	//}
	else if (body1->GetPosition().y < PIXEL_TO_METERS(-9001) && body1->GetPosition().y >= PIXEL_TO_METERS(-13000))
	{
		//LOG("ON THIRD IF=====================")
		gravity = -7.08f;
		float b = gravity;
		float m = (gravity) / PIXEL_TO_METERS(9000-13000);
		float forceGravity = m * body1->GetPosition().y + b;

		body1->AddForce(bhVec2(0, forceGravity));
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
	bhVec2 dragVec = { 0,0 };
	//if (b->GetPosition().y > PIXEL_TO_METERS(-800))
	//{
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

		dragVec = direction * forceDrag;
	//}

	return dragVec;
}

bhVec2 PhysicsEngine::AeroLift(bhBody* b)
{
	bhVec2 aeroLiftForce = { 0,0 };

	// Density of the air
	float airDensity = 2.5f;

	// Velocity of the body
	float velocity = b->GetLinearVelocity().GetNorm();

	// Area for the wing
	float areaWing = M_PI * b->GetBodyRadius() * b->GetBodyRadius() / 2;

	// Lift coefficient (FUYM)
	float liftCoefficient = 1.5f;

	// Formula
	float AeroLiftForce = 0.5 * airDensity * velocity * velocity * areaWing * liftCoefficient;
	
	// Current velocity
	bhVec2 direction = b->GetLinearVelocity().Normalize();

	aeroLiftForce = direction * AeroLiftForce;

	return aeroLiftForce;

}

bhVec2 PhysicsEngine::WaterPressure(bhBody* b)
{
	bhVec2 forcePressure = { 0,0 };
	// Variable that stores the water level that we want, for comfort
	bhVec2 waterLevel = { 0,PIXEL_TO_METERS(-800) };

	// First we have to check if the body is starting to touch the water level
	if (b->GetPosition().y + b->GetBodyRadius() >= waterLevel.y)
	{
		float angle = 0.0f;

		// We have 2 posible options, if we are fully inside the water, the angle is simply 360, this way we don't have to waste time calculating.
		// otherwise, we will calculate the angle with the formula.
		if ((b->GetPosition().y - waterLevel.y) > b->GetBodyRadius())
		{
			angle = 360.0f * M_PI / 180;
		}
		else
		{
			angle = 2 * acos((waterLevel.y - b->GetPosition().y) / b->GetBodyRadius());
		}

		if (angle >= 360.0f * M_PI / 180)
		{
			//  We calculate the area summerged with the formula
			float areaSummerged = ((pow(b->GetBodyRadius(), 2.0f) / 2) * (angle - sin(angle)));

			// The pression will vary with the position of the body, if the body is very far below it will have more pression
			float pressure = (b->GetPosition().y - waterLevel.y) * 2.0f;

			// We only calculate the pressure in half of the body since it's a circle
			float areaPressure = pressure * areaSummerged / 2;

			// The direction of the pressure will always go upwards
			bhVec2 direction = bhVec2(0, waterLevel.y - b->GetPosition().y).Normalize();

			// We do the same with the force of the pressure
			forcePressure = direction * areaPressure;

			// Finally we add pressure Force
			b->AddForce(forcePressure);
		}
		else
		{
			// All the statements below are the same like the ones above, but applied to the other angle
			float areaSummerged = ((pow(b->GetBodyRadius(), 2.0f) / 2) * (angle - sin(angle)));

			float pressure = (b->GetPosition().y - waterLevel.y) * 2.0f;

			float areaPressure = pressure * areaSummerged / 2;

			bhVec2 direction = { 0, (float)(waterLevel.y - b->GetPosition().y - b->GetBodyRadius()) };
			direction.Normalize();

			forcePressure = direction * areaPressure;

			b->AddForce(forcePressure);
		}
	}


	return forcePressure;
}

bhVec2 PhysicsEngine::HydroBuoy(bhBody* b)
{
	bhVec2 hydroBuoyForce = { 0,0 };

	// Variable that stores the water level that we want, for comfort
	bhVec2 waterLevel = { 0,PIXEL_TO_METERS(-800) };

	// Store gravity and density in variables for better understanding
	float gravity = 10.0f;

	float density = 4.0f;

	// First we have to check if the body is starting to touch the water level
	if (b->GetPosition().y + b->GetBodyRadius() >= waterLevel.y)
	{
		float angle = 0.0f;

		// We have 2 posible options, if we are fully inside the water, the angle is simply 360, this way we don't have to waste time calculating.
		// otherwise, we will calculate the angle with the formula.
		if ((b->GetPosition().y - waterLevel.y) > b->GetBodyRadius())
		{
			angle = 360.0f * M_PI / 180;
		}
		else
		{
			angle = 2 * acos((waterLevel.y - b->GetPosition().y) / b->GetBodyRadius());
		}

		if (angle >= 360.0f * M_PI / 180)
		{
			//  We calculate the area summerged with the formula
			float areaSummerged = ((pow(b->GetBodyRadius(), 2.0f) / 2) * (angle - sin(angle)));

			// The direction of the buoyancy will always go upwards
			bhVec2 direction = bhVec2(0, waterLevel.y - b->GetPosition().y).Normalize();

			// Finally we apply the force buoyancy formula
			float forceBuoyancy = density * gravity * areaSummerged;

			// We apply it to the direction we want, which is normalized
			hydroBuoyForce = direction * forceBuoyancy;

			// Finally we add all the forces we need, in this case, we need the hydro drag force, buoyancy.
			b->AddForce(hydroBuoyForce);
		}
		else
		{
			// All the statements below are the same like the ones above, but applied to the other angle
			float areaSummerged = ((pow(b->GetBodyRadius(), 2.0f) / 2) * (angle - sin(angle)));

			bhVec2 direction = { 0, (float)(waterLevel.y - b->GetPosition().y - b->GetBodyRadius()) };
			direction.Normalize();

			float forceBuoyancy = density * gravity * areaSummerged;
			hydroBuoyForce = direction * forceBuoyancy;

			b->AddForce(hydroBuoyForce);
		}
	}

	return hydroBuoyForce;
}

bhVec2 PhysicsEngine::HydroDrag(bhBody* b)
{
	// Variable that stores the water level that we want, for comfort
	bhVec2 waterLevel = { 0,PIXEL_TO_METERS(-800) };

	bhVec2 hydroDragForceVec = { 0,0 };

	// Check if the body is under water
	if (b->GetPosition().y + b->GetBodyRadius() >= waterLevel.y)
	{
		// Velocity friction coefficient
		float velocityCoef = 6.0f;

		// Current velocity of the object
		float velocity = b->GetLinearVelocity().GetNorm();

		// Calculate drag force
		float forceDrag = velocityCoef * velocity;

		// We get the direction of the body itself (Negate it, because drag always goes backwards from the velocity)
		bhVec2 direction = b->GetLinearVelocity().Normalize().Negate();

		// Multiply the force itself to the direction already calculated in the linea bove
		hydroDragForceVec = direction * forceDrag;

		b->AddForce(hydroDragForceVec);
	}

	return hydroDragForceVec;
}

void PhysicsEngine::Step(float dt)
{
	// Forces + Integrator ====================================

	p2List_item<bhBody*>* item = bodyList.getFirst();
	while (item != nullptr)
	{
		if (item->data->type == BodyType::DYNAMIC && item->data->IsActive())
		{
			item->data->SetAcceleration(bhVec2(0,0));
			item->data->ResetForce();
			ForceGravity(item->data);
			HydroBuoy(item->data);
			HydroDrag(item->data);
			WaterPressure(item->data);
			item->data->ApplyNewtonSecondLaw();
			Integrator(item->data->GetPosition(), item->data->GetLinearVelocity(), item->data->GetAcceleration(), dt);
		}
		else if(item->data->type == BodyType::NO_GRAVITY && item->data->IsActive())
			Integrator(item->data->GetPosition(), item->data->GetLinearVelocity(), item->data->GetAcceleration(), dt);
		else if (item->data->type == BodyType::SENSOR && item->data->IsActive())
			Integrator(item->data->GetPosition(), item->data->GetLinearVelocity(), item->data->GetAcceleration(), dt);

		item = item->next;
	}

	// Collisions ====================================

	for (p2List_item<bhBody*>* item = bodyList.getFirst(); item != nullptr; item = item->next)
	{
		for (p2List_item<bhBody*>* item2 = item->next; item2 != nullptr; item2 = item2->next)
		{
			if (item->data->GetName() != "missile" && item2->data->GetName() != "missile")
			{
				if (Intersection(item->data, item2->data) && item->data->IsActive())
				{
 					Collisions(item->data, item2->data);
				}
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

bool PhysicsEngine::Intersection(SDL_Rect rect, bhBody* b2)
{
	float x = b2->GetPosition().x - (PIXEL_TO_METERS(rect.x) + (PIXEL_TO_METERS(rect.w) / 2));
	float y = b2->GetPosition().y - (PIXEL_TO_METERS(rect.y) + (PIXEL_TO_METERS(rect.h) / 2));
	float dist = sqrt(pow(x, 2) + pow(y, 2));

	if (dist < (PIXEL_TO_METERS(rect.w) / 2) + b2->GetBodyRadius())
		return true;
	else
		return false;
}

void PhysicsEngine::Collisions(bhBody* b, bhBody* b2)
{
	// First we get the normal corresponding from the world to the body
	bhVec2 dir = b->GetPosition() - b2->GetPosition();

	// We normalize the vector, since we only want the direction
	dir = dir.Normalize();
	
	// We get the actual velocity of the spaceship
	// We get the speed as a float
	float speed = b->GetLinearVelocity().GetNorm();

	// We now multiply the speed for the direction so the spaceship knows the direction where it has to go to
	bhVec2 velocity = dir * speed * 0.6f;

	if (b2->type != BodyType::SENSOR)
		b->SetLinearVelocity(velocity);
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