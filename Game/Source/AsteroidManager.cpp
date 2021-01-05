#include "App.h"
#include "Texture.h"
#include "AsteroidManager.h"
#include "Physics.h"

AsteroidManager::AsteroidManager(App* parent, bool startEnabled) : Module(parent, startEnabled)
{
}

AsteroidManager::~AsteroidManager()
{
}

bool AsteroidManager::Start()
{
	texture = app->tex->Load("Assets/Textures/Asteroid.png");

	p2List_item<Asteroid*>* item = asteroidList.getFirst();

	while (item != nullptr)
	{
		item->data->Start();

		item = item->next;
	}

	return true;
}

update_status AsteroidManager::Update(float dt)
{
	p2List_item<Asteroid*>* item = asteroidList.getFirst();

	while (item != nullptr)
	{
		item->data->Update(dt);

		item = item->next;
	}

	return update_status::UPDATE_CONTINUE;
}

void AsteroidManager::Draw()
{
	p2List_item<Asteroid*>* item = asteroidList.getFirst();

	while (item != nullptr)
	{
		float rad = METERS_TO_PIXELS(item->data->GetBody()->GetBodyRadius());
		app->render->DrawTexture(item->data->texture, METERS_TO_PIXELS(item->data->GetBody()->GetPosition().x - rad), METERS_TO_PIXELS(item->data->GetBody()->GetPosition().y - rad), NULL);
		app->render->DrawCircle(METERS_TO_PIXELS(item->data->GetBody()->GetPosition().x), METERS_TO_PIXELS(item->data->GetBody()->GetPosition().y), rad, 255, 0, 0);

		item = item->next;
	}
}

bool AsteroidManager::CleanUp()
{
	p2List_item<Asteroid*>* item = asteroidList.getFirst();

	while (item != nullptr)
	{
		item->data->CleanUp();

		item = item->next;
	}

	return true;
}

Asteroid* AsteroidManager::CreateAsteroid(int radius, bhVec2 position)
{
	Asteroid* asteroid = new Asteroid();
	bhBody* asteroidBody = app->physics->CreateBody("asteroid", BodyType::NO_GRAVITY);
	position.x = PIXEL_TO_METERS(position.x);
	position.y = PIXEL_TO_METERS(position.y);
	asteroidBody->SetRadius(PIXEL_TO_METERS(radius));
	asteroidBody->SetPosition(position);
	asteroid->SetBody(asteroidBody);
	asteroid->texture = texture;

	asteroidList.add(asteroid);

	return asteroid;
}