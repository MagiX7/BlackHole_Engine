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

	body->SetPosition(bhVec2(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0)));
	body->SetLinearVelocity(bhVec2(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0)));
	body->SetMass(0.1);
	body->SetRadius(PIXEL_TO_METERS(10));
	body->SetMaxLinearVelocity(bhVec2(5, 5));
	
	return true;
}

update_status Spaceship::PreUpdate()
{


	return update_status::UPDATE_CONTINUE;
}

update_status Spaceship::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && -body->GetLinearVelocity().y < body->GetMaxLinearVelocity().y)
	{
		body->AddMomentum(bhVec2(PIXEL_TO_METERS(0), PIXEL_TO_METERS(-500.0f * dt)));
	}
	
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && body->GetLinearVelocity().x < body->GetMaxLinearVelocity().x)
	{
		body->AddMomentum(bhVec2(PIXEL_TO_METERS(500.0f * dt), PIXEL_TO_METERS(0)));
	}
	
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && -body->GetLinearVelocity().x < body->GetMaxLinearVelocity().x)
	{
		body->AddMomentum(bhVec2(PIXEL_TO_METERS(-500.0f * dt), PIXEL_TO_METERS(0)));
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && body->GetLinearVelocity().y < body->GetMaxLinearVelocity().y)
	{
		body->AddMomentum(bhVec2(PIXEL_TO_METERS(0), PIXEL_TO_METERS(500.0f * dt)));
	}

	LOG("%f  %f", body->GetPosition().x, body->GetPosition().y);
	//LOG("%f  %f", body->GetPosition());

	app->physics->Step(dt);

	return update_status::UPDATE_CONTINUE;
}

void Spaceship::Draw()
{
	app->render->DrawCircle(METERS_TO_PIXELS(body->GetPosition().x), METERS_TO_PIXELS(body->GetPosition().y), METERS_TO_PIXELS(body->GetBodyRadius()), 255, 0, 0);
}

bool Spaceship::CleanUp()
{
	return true;
}
