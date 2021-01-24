#include "App.h"
#include "Texture.h"
#include "AsteroidManager.h"
#include "Physics.h"

AsteroidManager::AsteroidManager()
{
}

AsteroidManager::~AsteroidManager()
{
}

bool AsteroidManager::Start()
{
	p2List_item<Asteroid*>* item = asteroidList.getFirst();

	while (item != nullptr)
	{
		item->data->Start();

		item = item->next;
	}

	return true;
}

bool AsteroidManager::Update(float dt)
{
	p2List_item<Asteroid*>* item = asteroidList.getFirst();

	while (item != nullptr)
	{
		item->data->Update(dt);
		if (item->data->dieAnim.HasFinished()) asteroidList.del(item);
		item = item->next;
	}

	return true;
}

void AsteroidManager::Draw(Render* render)
{
	p2List_item<Asteroid*>* item = asteroidList.getFirst();

	while (item != nullptr)
	{
		float rad = METERS_TO_PIXELS(item->data->GetBody()->GetBodyRadius());
		render->DrawTexture(item->data->texture, METERS_TO_PIXELS(item->data->GetBody()->GetPosition().x - rad), METERS_TO_PIXELS(item->data->GetBody()->GetPosition().y - rad), &item->data->dieAnim.GetCurrentFrame());
		render->DrawCircle(METERS_TO_PIXELS(item->data->GetBody()->GetPosition().x), METERS_TO_PIXELS(item->data->GetBody()->GetPosition().y), rad, 255, 0, 0);

		item = item->next;
	}
}

bool AsteroidManager::CleanUp(Texture* tex)
{
	LOG("Unloading Asteroid Manager");
	p2List_item<Asteroid*>* item = asteroidList.getFirst();

	while (item != nullptr)
	{
		item->data->CleanUp();

		item = item->next;
	}

	tex->UnLoad(texture);
	asteroidList.clear();

	return true;
}

Asteroid* AsteroidManager::CreateAsteroid(int radius, bhVec2 position, Physics* physics)
{
	Asteroid* asteroid = new Asteroid();
	bhBody* asteroidBody = physics->CreateBody("asteroid", BodyType::NO_GRAVITY);
	position.x = PIXEL_TO_METERS(position.x);
	position.y = PIXEL_TO_METERS(position.y);
	asteroidBody->SetRadius(PIXEL_TO_METERS(radius));
	asteroidBody->SetPosition(position);
	asteroid->SetBody(asteroidBody);
	asteroid->texture = texture;

	asteroidList.add(asteroid);

	return asteroid;
}

void AsteroidManager::DestroyAsteroid(Asteroid* ast, Physics* physics)
{
	p2List_item<Asteroid*>* item = asteroidList.getFirst();

	while (item != nullptr)
	{
		if (item->data == ast)
		{
			physics->DestroyBody(item->data->GetBody());
			physics->GetWorld()->DeleteBody(item->data->GetBody());
			break;
		}

		item = item->next;
	}
}

void AsteroidManager::SetTexture(Texture* tex)
{
	texture = tex->Load("Assets/Textures/Asteroid.png");
}

bool AsteroidManager::CheckCollision(bhBody* body, Physics* physics)
{
	p2List_item<Asteroid*>* item = asteroidList.getFirst();

	while (item != nullptr)
	{
		if (physics->GetWorld()->Intersection(body, item->data->GetBody()))
		{
			if (body->GetName() == "missile")
			{
				DestroyAsteroid(item->data, physics);
				item->data->die = true;
			}
			return true;
		}
		item = item->next;
	}

	return false;
}

bool AsteroidManager::CheckCollision(SDL_Rect rect, Physics* physics)
{
	p2List_item<Asteroid*>* item = asteroidList.getFirst();

	while (item != nullptr)
	{
		if (physics->GetWorld()->Intersection(rect, item->data->GetBody()))
		{
			physics->DestroyBody(item->data->GetBody());
			asteroidList.del(item);
			return true;
		}
		item = item->next;
	}

	return false;
}