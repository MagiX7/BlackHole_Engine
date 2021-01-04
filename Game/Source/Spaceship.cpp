#include "App.h"
#include "Texture.h"
#include "Render.h"


#include "Spaceship.h"

Spaceship::Spaceship(App* app, bool start_enabled) : Module(app, start_enabled)
{
	idleAnim.PushBack({ 11,13, 18,15 });
}

Spaceship::~Spaceship()
{
}

bool Spaceship::Start()
{
	texture = app->tex->Load("Assets/Textures/spaceship.png");

	body = app->physics->CreateBody("spaceship");

	body->SetPosition(bhVec2(PIXEL_TO_METERS(500), PIXEL_TO_METERS(0)));
	body->SetLinearVelocity(bhVec2(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0)));
	body->SetMass(0.1);
	body->SetRadius(PIXEL_TO_METERS(18));
	body->SetMaxLinearVelocity(bhVec2(PIXEL_TO_METERS(500), PIXEL_TO_METERS(500)));
	body->SetBodyAngle(0 * M_PI / 180);
	fuel = 50.0f;
	
	currentAnim = &idleAnim;

	return true;
}

update_status Spaceship::PreUpdate()
{


	return update_status::UPDATE_CONTINUE;
}

update_status Spaceship::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && -body->GetLinearVelocity().y < body->GetMaxLinearVelocity().y && fuel > 0)
	{
		double angle = body->GetBodyAngle();
		bhVec2 mom = bhVec2(cos(angle - 90 * M_PI / 180), sin(angle - 90 * M_PI / 180));
		body->AddMomentum(bhVec2(PIXEL_TO_METERS(mom.x), PIXEL_TO_METERS(mom.y)));

		//fuel -= (5.0f * dt);
	}
	
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && body->GetLinearVelocity().x < body->GetMaxLinearVelocity().x)
	{
		double angle = body->GetBodyAngle();
		angle += 2 * M_PI / 180;
		
		if (angle == 360)
			angle = 0;

		body->SetBodyAngle(angle);
	}
	
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && -body->GetLinearVelocity().x < body->GetMaxLinearVelocity().x)
	{
		double angle = body->GetBodyAngle();
		angle -= 2 * M_PI / 180;

		if (angle == 360)
			angle = 0;

		body->SetBodyAngle(angle);
	}

	LOG("%f  %f", body->GetPosition().x, body->GetPosition().y);

	if (fuel < 0) fuel = 0;

	LOG("%f", fuel);

	currentAnim->Update();

	return update_status::UPDATE_CONTINUE;
}

void Spaceship::Draw()
{
	app->render->DrawTexture(texture, METERS_TO_PIXELS(body->GetPosition().x - 18), METERS_TO_PIXELS(body->GetPosition().y - 14), NULL, 1.0f, body->GetBodyAngle() * 180 / M_PI);

	app->render->DrawCircle(METERS_TO_PIXELS(body->GetPosition().x), METERS_TO_PIXELS(body->GetPosition().y), METERS_TO_PIXELS(body->GetBodyRadius()), 255, 0, 0);
}

bool Spaceship::CleanUp()
{
	app->tex->Unload(texture);

	return true;
}