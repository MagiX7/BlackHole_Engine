#include "App.h"
#include "Texture.h"
#include "Render.h"
#include "Physics.h"
#include "AsteroidManager.h"
#include "AstronautManager.h"

#include "Spaceship.h"
#include "SceneGameplay.h"

#define MISSILE_SPEED 500

Spaceship::Spaceship(App* parent, SceneGameplay* gameplay)
{
	//idleAnim.PushBack({ 11,13, 18,15 });

	idleAnim.PushBack({ 358,133,36,35 });
	
	flyAnim.PushBack({ 398,133,36,35 });
	
	engineOnAnim.PushBack({ 358,179,36,35 });
	engineOnAnim.PushBack({ 396,179,36,35 });
	engineOnAnim.PushBack({ 434,179,36,35 });
	engineOnAnim.loop = true;

	/*explosionAnim.PushBack({ 16,15,36,34 });
	explosionAnim.PushBack({ 66,12,40,39 });
	explosionAnim.PushBack({ 117,11,44,44 });
	explosionAnim.PushBack({ 168,8,49,49 });
	explosionAnim.PushBack({ 229,6,53,50 });
	explosionAnim.PushBack({ 287,6,56,52 });
	explosionAnim.PushBack({ 415,5,58,53 });
	explosionAnim.PushBack({ 3,82,57,53 });
	explosionAnim.PushBack({ 77,81,58,52 });
	explosionAnim.PushBack({ 154,78,58,53 });
	explosionAnim.PushBack({ 234,80,56,53 });
	explosionAnim.PushBack({ 317,77,53,53 });
	explosionAnim.PushBack({ 10,158,53,53 });
	explosionAnim.PushBack({ 67,161,53,53 });
	explosionAnim.PushBack({ 73,163,53,53 });
	explosionAnim.PushBack({ 142,155,53,53 });*/

	explosionAnim.PushBack({ 5,6,58,52 });
	explosionAnim.PushBack({ 57,6,58,52 });
	explosionAnim.PushBack({ 110,7,58,52 });
	explosionAnim.PushBack({ 165,6,58,52 });
	explosionAnim.PushBack({ 226,5,58,52 });
	explosionAnim.PushBack({ 349,5,58,52 });
	explosionAnim.PushBack({ 415,5,58,52 });
	explosionAnim.PushBack({ 3,82,58,52 });
	explosionAnim.PushBack({ 78,81,58,52 });
	explosionAnim.PushBack({ 154,81,58,52 });
	explosionAnim.PushBack({ 234,80,58,52 });
	explosionAnim.PushBack({ 316,76,58,52 });
	explosionAnim.PushBack({ 399,73,58,52 });
	explosionAnim.PushBack({ 5,155,58,52 });
	explosionAnim.PushBack({ 140,157,58,52 });
	explosionAnim.PushBack({ 206,156,58,52 });
	explosionAnim.loop = false;

	this->app = parent;
	this->scene = gameplay;
}

Spaceship::~Spaceship()
{
}

bool Spaceship::Start()
{
	body = app->physics->CreateBody("spaceship", BodyType::DYNAMIC);
	
	body->SetPosition(bhVec2(PIXEL_TO_METERS(500), PIXEL_TO_METERS(-3000)));
	body->SetLinearVelocity(bhVec2(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0)));
	body->SetMass(10);
	body->SetRadius(PIXEL_TO_METERS(18));
	//body->SetMaxLinearVelocity(bhVec2(PIXEL_TO_METERS(500), PIXEL_TO_METERS(500)));
	body->SetBodyAngle(0);

	fuel = 100.0f;
	health = 100;

	astronautsCollected = 0;
	
	currentAnim = &idleAnim;

	texture = app->tex->Load("Assets/Textures/Spaceship/sheet.png");
	scoreFx = app->audio->LoadFx("Assets/Audio/pickup_fx.wav");
	scoreTexture = app->tex->Load("Assets/Textures/astronaut_score.png");

	char lookupTable[] = { "0123456789?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!    " };
	fontsIndex = app->fonts->Load("Assets/Textures/fonts.png", lookupTable, 1);

	astronautFx = app->audio->LoadFx("Assets/Audio/astronaut_fx.wav");

	return true;
}

update_status Spaceship::PreUpdate()
{

	return update_status::UPDATE_CONTINUE;
}

update_status Spaceship::Update(float dt, AsteroidManager* asteroid, AstronautManager* astronaut)
{
	//body->ResetForce();
	//body->SetAcceleration(bhVec2(0, 0));

	if (body->GetPosition().x < PIXEL_TO_METERS(-7)) body->SetPosition(bhVec2(PIXEL_TO_METERS(1040), body->GetPosition().y));
	else if(body->GetPosition().x > PIXEL_TO_METERS(1040)) body->SetPosition(bhVec2(PIXEL_TO_METERS(-7), body->GetPosition().y));

	engineOnAnim.speed = 200 * dt;
	explosionAnim.speed = 400 * dt;

	if (health > 0)
	{
		HandleInput(dt);

		if ((app->physics->GetWorld()->Intersection(body, scene->earth) || app->physics->GetWorld()->Intersection(body, scene->moon)) &&
			fabs(body->GetLinearVelocity().y) > 0.5f || fabs(body->GetLinearVelocity().x) > 0.5f)
		{
			Dead();
		}

		if (asteroid->CheckCollision(body, app->physics) == true)
		{
			Dead();
		}

		if (astronaut->CheckCollision(body, app->physics) == true)
		{
			AddScore();
			int num = rand() % 10;
			if (num >= 5) app->audio->PlayFx(astronautFx);			
		}
	}
	else if (health <= 0)
	{
		body->SetLinearVelocity(0, 0);
		if (explosionAnim.HasFinished()) body->SetActive(false);
	}

	// Update missiles ===============================
	if (missiles.count() > 0)
	{
		p2List_item<Missile*>* item = missiles.getFirst();
		while (item != nullptr)
		{
			item->data->position.x += item->data->direction.x * MISSILE_SPEED * dt;
			item->data->position.y += item->data->direction.y * MISSILE_SPEED * dt;
			item->data->collider.x = item->data->position.x;
			item->data->collider.y = item->data->position.y;

			item = item->next;
		}
	}


	LOG("POS ================= %f  %f", METERS_TO_PIXELS(body->GetPosition().x), METERS_TO_PIXELS(body->GetPosition().y));

	//LOG("%f  %f", body->GetLinearVelocity().x, body->GetLinearVelocity().y)
	/*LOG("TOTAL FORCE ================================================= %f", body->GetTotalForce())*/

	if (fuel < 0) fuel = 0;

	currentAnim->Update(dt);

	sprintf_s(scoreAstronautsText , 4, "%d", astronautsCollected);
	sprintf_s(fuelText, 8, "%d", (int)fuel);

	return update_status::UPDATE_CONTINUE;
}

void Spaceship::Draw()
{
	// Draw spaceship =======================
	if(currentAnim == &explosionAnim)
		app->render->DrawTexture(texture, METERS_TO_PIXELS(body->GetPosition().x - 28), METERS_TO_PIXELS(body->GetPosition().y - 25), &currentAnim->GetCurrentFrame(), 1.0f, body->GetBodyAngle() * 180 / M_PI);
	else
		app->render->DrawTexture(texture, METERS_TO_PIXELS(body->GetPosition().x - 18), METERS_TO_PIXELS(body->GetPosition().y - 15), &currentAnim->GetCurrentFrame(), 1.0f, body->GetBodyAngle() * 180 / M_PI);

	// Draw missiles ========================
	if (missiles.count() > 0)
	{
		p2List_item<Missile*>* item = missiles.getFirst();
		while (item != nullptr)
		{
			app->render->DrawQuad(item->data->collider, 255, 0, 0, 255);
			item = item->next;
		}
	}

	// Draw collider =======================
	app->render->DrawCircle(METERS_TO_PIXELS(body->GetPosition().x), METERS_TO_PIXELS(body->GetPosition().y), METERS_TO_PIXELS(body->GetBodyRadius()), 255, 0, 0);

	// Draw text ===========================
	app->fonts->drawText(80, 20, fontsIndex, scoreAstronautsText);
	app->fonts->drawText(63, 25, fontsIndex, "x");
	app->render->DrawTexture(scoreTexture, 20 + app->render->camera.x, 20 - (app->render->camera.y), NULL);

	app->fonts->drawText(15, 75, fontsIndex, "Fuel");
	app->fonts->drawText(170, 75, fontsIndex, fuelText);
}

bool Spaceship::CleanUp()
{
	app->tex->UnLoad(texture);
	app->tex->UnLoad(scoreTexture);
	app->physics->DestroyBody(body);

	if (missiles.count() > 0)missiles.clear();

	return true;
}

void Spaceship::CreateMissile()
{
	Missile* missile = new Missile();
	float x = METERS_TO_PIXELS(body->GetPosition().x);
	float y = METERS_TO_PIXELS(body->GetPosition().y);
	missile->position = { x, y };
	missile->direction = { (float)cos((body->GetBodyAngle())), (float)sin((body->GetBodyAngle())) };

	float dirNorm = sqrt(missile->direction.x * missile->direction.x + missile->direction.y * missile->direction.y);
	missile->direction.x /= dirNorm;
	missile->direction.y /= dirNorm;

	missiles.add(missile);
}

void Spaceship::HandleInput(float dt)
{
	// Create missiles
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		CreateMissile();

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

	//======================================
	
	// Movement input

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && fuel > 0)
	{
		if (currentAnim != &engineOnAnim)
		{
			engineOnAnim.Reset();
			currentAnim = &engineOnAnim;
		}

		double angle = body->GetBodyAngle();
		bhVec2 mom = bhVec2(cos(angle - 90 * M_PI / 180), sin(angle - 90 * M_PI / 180));
			
		body->AddMomentum(bhVec2(PIXEL_TO_METERS(mom.x * 10), PIXEL_TO_METERS(mom.y * 10)));
			
		fuel -= (1.2f * dt);
	}

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_UP)
	{
		if (currentAnim != &flyAnim)
		{
			flyAnim.Reset();
			currentAnim = &flyAnim;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		body->Rotate(2);
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		body->Rotate(-2);
	}

	
	//==============================================
	// Add Momentum with force

	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		if(currentAnim != &engineOnAnim)
		{
			engineOnAnim.Reset();
			currentAnim = &engineOnAnim;
		}


		double angle = body->GetBodyAngle();
		bhVec2 mom = bhVec2(cos(angle - 90 * M_PI / 180), sin(angle - 90 * M_PI / 180));
			
		bhVec2 f = { (float)mom.x * 1000, (float)mom.y * 1000 };
		body->AddMomentumWithForce(bhVec2(PIXEL_TO_METERS(f.x * dt), PIXEL_TO_METERS(f.y * dt)), dt);

		fuel -= (1.2f * dt);
	}
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
	{
		if (currentAnim != &flyAnim)
		{
			flyAnim.Reset();
			currentAnim = &flyAnim;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		body->Rotate(2);
	}

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		body->Rotate(-2);
	}
}

void Spaceship::Dead()
{
	if (currentAnim != &explosionAnim)
	{
		health = 0;
		body->SetLinearVelocity(0, 0);
		explosionAnim.Reset();
		currentAnim = &explosionAnim;
	}
}

void Spaceship::AddScore()
{
	astronautsCollected++;
	app->audio->PlayFx(scoreFx);
}

void Spaceship::AddHealth(float h)
{
	health += h;
}

void Spaceship::AddFuel(float f)
{
	fuel += f;
}

void Spaceship::AddAmmo(int a)
{
	ammo += a;
}

float Spaceship::GetFuel()
{
	return fuel;
}