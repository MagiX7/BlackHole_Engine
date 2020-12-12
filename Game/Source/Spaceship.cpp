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
	body = app->physics->CreateBody("spaceship");

	body->SetPosition(bhVec2(PIXEL_TO_METERS(100), PIXEL_TO_METERS(100)));
	body->SetLinearVelocity(bhVec2(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0)));
	body->SetMass(0.1);
	body->SetRadius(PIXEL_TO_METERS(10));
	
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
		body->AddMomentum(bhVec2(PIXEL_TO_METERS(0), PIXEL_TO_METERS(-10.0f)));
	}
	
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		body->AddMomentum(bhVec2(PIXEL_TO_METERS(10), PIXEL_TO_METERS(0)));
	}
	
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		body->AddMomentum(bhVec2(PIXEL_TO_METERS(-10), PIXEL_TO_METERS(0)));
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		body->AddMomentum(bhVec2(PIXEL_TO_METERS(0), PIXEL_TO_METERS(10)));
	}

	app->physics->Step(0.016);

	Draw();

	return update_status::UPDATE_CONTINUE;
}

void Spaceship::Draw()
{
	app->render->DrawCircle(METERS_TO_PIXELS(body->GetPosition().x), METERS_TO_PIXELS(body->GetPosition().y), METERS_TO_PIXELS(body->GetBodyRadius()), 255, 255, 255);
}

bool Spaceship::CleanUp()
{
	return true;
}
