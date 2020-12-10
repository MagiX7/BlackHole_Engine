#include "App.h"
#include "Texture.h"
#include "Render.h"

#include "Spaceship.h"

Spaceship::Spaceship(App* app, bool start_enabled) : Module(app, start_enabled)
{
}

Spaceship::~Spaceship()
{
}

bool Spaceship::Start()
{
	SetPosition(bhVec2(100, 100));
	SetLinearVelocity(bhVec2(0, 0));
	SetMass(0.1);
	
	return true;
}

update_status Spaceship::PreUpdate()
{


	return update_status::UPDATE_CONTINUE;
}

update_status Spaceship::Update()
{
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		AddMomentum(bhVec2(0, -10.0f));
	}
	
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		AddMomentum(bhVec2(10, 0));
	}
	
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		AddMomentum(bhVec2(-10, 0));
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		AddMomentum(bhVec2(0, -10));
	}

	app->physics->Step(0.016);

	Draw();

	return update_status::UPDATE_CONTINUE;
}

void Spaceship::Draw()
{
	app->render->DrawCircle(GetPosition().x, GetPosition().y, 10, 255, 255, 255);
}

bool Spaceship::CleanUp()
{
	return true;
}
