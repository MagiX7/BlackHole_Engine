#pragma once

#include "Module.h"
#include "SString.h"
#include "p2List.h"

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) PIXELS_PER_METER * m)
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

class bhVec2;
class bhBody;

class PhysicsEngine : public Module
{
public:
	PhysicsEngine(App* app, bool start_enabled = true);
	~PhysicsEngine();

	bhVec2 ForceGravity(float gravity, float mass1, float mass2, float distance, bhVec2 direction);
	bhVec2 Gravity();
	bhVec2 AeroDrag(bhBody* b);
	bhVec2 AeroLift(bhBody* b);
	bhVec2 HydroBuoy(bhBody* b);
	bhVec2 HydroDrag(bhBody* b);

	void Step(float dt);

	bool Intersection(bhBody* b1, bhBody* b2);
	void Collisions(bhBody* b, bhBody* b2);

	bhBody* CreateBody(SString n, BodyType type);

	void DestroyBody(bhBody* b);

private:

	void Integrator(bhVec2& x, bhVec2& v, bhVec2& a, float dt);

	bhVec2 gravity;
	float aeroDrag;
	float aeroLift;
	float hydroBuoy;
	float hydroDrag;

	p2List<bhBody*> bodyList;
};