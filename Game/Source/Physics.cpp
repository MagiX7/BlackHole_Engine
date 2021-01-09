#include "Physics.h"
#include "Globals.h"

Physics::Physics(App* app, bool start_enabled) : Module(app, start_enabled)
{
}

Physics::~Physics()
{
}

bool Physics::Start()
{
	world = new PhysicsEngine();

	return true;
}

update_status Physics::PreUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

update_status Physics::Update(float dt)
{
	world->Step(dt);

	return update_status::UPDATE_CONTINUE;
}

update_status Physics::PostUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

bool Physics::CleanUp()
{
	bodies.clear();

	return true;
}

bhBody* Physics::CreateBody(SString n, BodyType type)
{
	bhBody* b = new bhBody(n, type);

	// Add the body to the list in module physics
	bodies.add(b);

	// And also to the world
	world->AddBody(b);

	return b;
}

void Physics::DestroyBody(bhBody* b)
{
	p2List_item<bhBody*>* item = bodies.getFirst();

	while (item != nullptr)
	{
		if (item->data == b)
			bodies.del(item);

		item = item->next;
	}
}
