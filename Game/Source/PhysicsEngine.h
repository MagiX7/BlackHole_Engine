#pragma once

#include "SString.h"
#include "p2List.h"
#include "bhBody.h"

class bhVec2;

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	bhVec2 ForceGravity(float gravity, float mass1, float mass2, float distance, bhVec2 direction);
	void ForceGravity(bhBody& body1);


	bhVec2 Gravity();
	bhVec2 AeroDrag(bhBody* b);
	bhVec2 AeroLift(bhBody* b);
	bhVec2 HydroBuoy(bhBody* b);
	bhVec2 HydroDrag(bhBody* b);

	void Step(float dt);

	bool Intersection(bhBody* b1, bhBody* b2);
	void Collisions(bhBody* b, bhBody* b2);


	void AddBody(bhBody* b);
	void DeleteBody(bhBody* b);

private:

	void Integrator(bhVec2& x, bhVec2& v, bhVec2& a, float dt);

private:

	bhVec2 gravity;
	float aeroDrag;
	float aeroLift;
	float hydroBuoy;
	float hydroDrag;


	p2List<bhBody*> bodyList;

};