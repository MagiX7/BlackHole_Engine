#include "App.h"
#include "Texture.h"
#include "Render.h"
#include "Physics.h"

#include "Spaceship.h"

Spaceship::Spaceship(App* app, bool start_enabled) : Module(app, start_enabled)
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

}

Spaceship::~Spaceship()
{
}

bool Spaceship::Start()
{
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

	texture = app->tex->Load("Assets/Textures/Spaceship/sheet.png");
	scoreFx = app->audio->LoadFx("Assets/Audio/pickup_fx.wav");
	scoreTexture = app->tex->Load("Assets/Textures/astronaut_score.png");


	char lookupTable[] = { "0123456789?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!    " };
	fontsIndex = app->fonts->Load("Assets/Textures/fonts.png", lookupTable, 1);

	return true;
}

update_status Spaceship::PreUpdate()
{


	return update_status::UPDATE_CONTINUE;
}

update_status Spaceship::Update(float dt)
{
	engineOnAnim.speed = 200 * dt;
	explosionAnim.speed = 400 * dt;

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

	if (app->physics->GetWorld()->Intersection(body, app->scene->floor) && fabs(body->GetLinearVelocity().y) > 2)
	{
		health = 0;
		body->SetLinearVelocity(0, 0);
		if (currentAnim != &explosionAnim)
		{
			explosionAnim.Reset();
			currentAnim = &explosionAnim;
		}
	}

	if (app->asteroidManager->CheckCollision(body) == true)
	{
		health = 0;
		body->SetLinearVelocity(0, 0);
		if (currentAnim != &explosionAnim)
		{
			explosionAnim.Reset();
			currentAnim = &explosionAnim;
		}
	}

	p2List_item <Astronaut*>* item = app->astronautManager->astronautsList.getFirst();

	while (item != nullptr)
	{
		if (app->physics->GetWorld()->Intersection(body, item->data->GetBody()))
		{
			app->astronautManager->DeleteAstronaut(item->data->GetBody());
			AddScore();
		}

		item = item->next;
	}

	if (health <= 0)
	{
		if (explosionAnim.HasFinished())
		{
			body->SetActive(false);
			CleanUp();
		}
	}


	//LOG("%f  %f", body->GetPosition().x, body->GetPosition().y);
	LOG("%f  %f", body->GetLinearVelocity().x, body->GetLinearVelocity().y);

	if (fuel < 0) fuel = 0;

	currentAnim->Update(dt);

	sprintf_s(scoreAstronautsText , 4, "%d", astronautsCollected);

	return update_status::UPDATE_CONTINUE;
}

void Spaceship::Draw()
{
	// Draw spaceship
	if(currentAnim == &explosionAnim)
		app->render->DrawTexture(texture, METERS_TO_PIXELS(body->GetPosition().x - 28), METERS_TO_PIXELS(body->GetPosition().y - 25), &currentAnim->GetCurrentFrame(), 1.0f, body->GetBodyAngle() * 180 / M_PI);
	else

	app->render->DrawTexture(texture, METERS_TO_PIXELS(body->GetPosition().x - 18), METERS_TO_PIXELS(body->GetPosition().y - 15), &currentAnim->GetCurrentFrame(), 1.0f, body->GetBodyAngle() * 180 / M_PI);
	
	if (missile != nullptr)
		app->render->DrawQuad({ (int)body->GetPosition().x, (int)body->GetPosition().y, 2,8 }, 255, 0, 0, 200);

	// Draw collider
	app->render->DrawCircle(METERS_TO_PIXELS(body->GetPosition().x), METERS_TO_PIXELS(body->GetPosition().y), METERS_TO_PIXELS(body->GetBodyRadius()), 255, 0, 0);

	app->fonts->drawText(80, 20, fontsIndex, scoreAstronautsText);
	app->fonts->drawText(63, 25, fontsIndex, "x");
	app->render->DrawTexture(scoreTexture, 20 + app->render->camera.x, 20 - (app->render->camera.y), NULL);

}

bool Spaceship::CleanUp()
{
	app->tex->UnLoad(texture);
	app->tex->UnLoad(scoreTexture);
	app->physics->DestroyBody(body);


	return true;
}

void Spaceship::LaunchMissile()
{
}

void Spaceship::AddScore()
{
	astronautsCollected++;
	app->audio->PlayFx(scoreFx);
}
