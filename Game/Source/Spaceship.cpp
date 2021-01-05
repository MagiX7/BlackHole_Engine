#include "App.h"
#include "Texture.h"
#include "Render.h"


#include "Spaceship.h"

Spaceship::Spaceship(App* app, bool start_enabled) : Module(app, start_enabled)
{
	//idleAnim.PushBack({ 11,13, 18,15 });

	idleAnim.PushBack({ 0,0,36,35 });
	
	flyAnim.PushBack({ 40,0,36,35 });
	
	engineOnAnim.PushBack({ 0,46,36,35 });
	engineOnAnim.PushBack({ 38,46,36,35 });
	engineOnAnim.PushBack({ 76,46,36,35 });
	engineOnAnim.loop = true;

}

Spaceship::~Spaceship()
{
}

bool Spaceship::Start()
{
	texture = app->tex->Load("Assets/Textures/Spaceship/spaceship_sheet.png");

	body = app->physics->CreateBody("spaceship", BodyType::DYNAMIC);

	body->SetPosition(bhVec2(PIXEL_TO_METERS(500), PIXEL_TO_METERS(0)));
	body->SetLinearVelocity(bhVec2(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0)));
	body->SetMass(0.1);
	body->SetRadius(PIXEL_TO_METERS(18));
	body->SetMaxLinearVelocity(bhVec2(PIXEL_TO_METERS(500), PIXEL_TO_METERS(500)));
	body->SetBodyAngle(0);
	fuel = 50.0f;
	astronautsCollected = 0;
	
	currentAnim = &idleAnim;

	return true;
}

update_status Spaceship::PreUpdate()
{


	return update_status::UPDATE_CONTINUE;
}

update_status Spaceship::Update(float dt)
{
	engineOnAnim.speed = 200 * dt;

	if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
	{
		if (currentAnim != &flyAnim)
		{
			flyAnim.Reset();
			currentAnim = &flyAnim;
		}
		else if (currentAnim != &idleAnim)
		{
			idleAnim.Reset();
			currentAnim = &idleAnim;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && -body->GetLinearVelocity().y < body->GetMaxLinearVelocity().y && fuel > 0)
	{
		if (currentAnim != &engineOnAnim)
		{
			engineOnAnim.Reset();
			currentAnim = &engineOnAnim;
		}

		double angle = body->GetBodyAngle();
		bhVec2 mom = bhVec2(cos(angle - 90 * M_PI / 180), sin(angle - 90 * M_PI / 180));
		body->AddMomentum(bhVec2(PIXEL_TO_METERS(mom.x * dt * 250), PIXEL_TO_METERS(mom.y * dt * 250)));

		//fuel -= (1.2f * dt);
	}
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_UP)
	{
		if (currentAnim != &flyAnim)
		{
			flyAnim.Reset();
			currentAnim = &flyAnim;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && body->GetLinearVelocity().x < body->GetMaxLinearVelocity().x)
	{
		body->Rotate(2);
	}
	
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && -body->GetLinearVelocity().x < body->GetMaxLinearVelocity().x)
	{
		body->Rotate(-2);
	}

	LOG("%f  %f", body->GetPosition().x, body->GetPosition().y);

	if (fuel < 0) fuel = 0;

	LOG("%f", fuel);

	currentAnim->Update(dt);

	return update_status::UPDATE_CONTINUE;
}

void Spaceship::Draw()
{
	// Draw spaceship
	app->render->DrawTexture(texture, METERS_TO_PIXELS(body->GetPosition().x - 18), METERS_TO_PIXELS(body->GetPosition().y - 15), &currentAnim->GetCurrentFrame(), 1.0f, body->GetBodyAngle() * 180 / M_PI);
	
	if (missile != nullptr)
		app->render->DrawQuad({ (int)body->GetPosition().x, (int)body->GetPosition().y, 2,8 }, 255, 0, 0, 200);

	// Draw collider
	app->render->DrawCircle(METERS_TO_PIXELS(body->GetPosition().x), METERS_TO_PIXELS(body->GetPosition().y), METERS_TO_PIXELS(body->GetBodyRadius()), 255, 0, 0);
}

bool Spaceship::CleanUp()
{
	app->tex->Unload(texture);

	return true;
}

void Spaceship::LaunchMissile()
{
}