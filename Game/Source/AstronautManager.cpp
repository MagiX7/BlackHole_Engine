#include "App.h"
#include "Texture.h"
#include "AstronautManager.h"
#include "Physics.h"


AstronautManager::AstronautManager()
{
}

bool AstronautManager::Start()
{
	p2List_item<Astronaut*>* item = astronautsList.getFirst();

	while (item != nullptr)
	{
		item->data->Start();

		item = item->next;
	}

	return true;
}

bool AstronautManager::Update(float dt)
{
	p2List_item<Astronaut*>* item = astronautsList.getFirst();

	while (item != nullptr)
	{
		item->data->Update(dt);

		item = item->next;
	}

	return true;
}

bool AstronautManager::CleanUp(Texture* tex)
{
	LOG("Unloading Astronaut Manager");
	p2List_item<Astronaut*>* item = astronautsList.getFirst();

	while (item != nullptr)
	{
		item->data->CleanUp();

		item = item->next;
	}
	
	tex->UnLoad(astronautTexture);
	astronautsList.clear();

	return true;
}

void AstronautManager::Draw(Render* render, bool debug)
{
	p2List_item<Astronaut*>* item = astronautsList.getFirst();

	while (item != nullptr)
	{
		render->DrawTexture(item->data->texture, METERS_TO_PIXELS(item->data->GetBody()->GetPosition().x - 15), METERS_TO_PIXELS(item->data->GetBody()->GetPosition().y - 15), NULL, 1.0f, item->data->GetBody()->GetBodyAngle() * 180 / M_PI);
		if (debug) render->DrawCircle(METERS_TO_PIXELS(item->data->GetBody()->GetPosition().x), METERS_TO_PIXELS(item->data->GetBody()->GetPosition().y), METERS_TO_PIXELS(item->data->GetBody()->GetBodyRadius()), 255, 0, 0);
		
		item = item->next;
	}
}

Astronaut* AstronautManager::CreateAstronaut(int radius, bhVec2 initialPos, Physics* physics)
{
	Astronaut* astronaut = new Astronaut();
	bhBody* astronautBody = physics->CreateBody("astronaut", BodyType::SENSOR);
	initialPos.x = PIXEL_TO_METERS(initialPos.x);
	initialPos.y = PIXEL_TO_METERS(initialPos.y);
	astronaut->SetInitialPos(initialPos);
	astronautBody->SetBodyAngle((0.0f * M_PI / 180));
	astronautBody->SetRadius(PIXEL_TO_METERS(radius));
	astronautBody->SetPosition(initialPos);
	astronaut->SetBody(astronautBody);
	astronaut->texture = astronautTexture;

	astronautsList.add(astronaut);

	return astronaut;
}

void AstronautManager::DeleteAstronaut(Astronaut* astronaut, Physics* physics)
{
	p2List_item<Astronaut*>* item = astronautsList.getFirst();

	while (item != nullptr)
	{
		if (item->data == astronaut)
		{
			physics->DestroyBody(item->data->GetBody());
			physics->GetWorld()->DeleteBody(item->data->GetBody());
			delete item->data;
			astronautsList.del(item);
			break;
		}

		item = item->next;
	}

}

void AstronautManager::DeleteAstronaut(bhBody* astronaut, Physics* physics)
{
	p2List_item<Astronaut*>* item = astronautsList.getFirst();

	while (item != nullptr)
	{
		if (item->data->GetBody() == astronaut)
		{
			physics->DestroyBody(item->data->GetBody());
			physics->GetWorld()->DeleteBody(item->data->GetBody());
			delete item->data;
			astronautsList.del(item);
			break;
		}

		item = item->next;
	}
}

void AstronautManager::SetTexture(Texture* tex)
{
	astronautTexture = tex->Load("Assets/Textures/astronaut.png");
}


bool AstronautManager::CheckCollision(bhBody* body, Physics* physics)
{
	p2List_item<Astronaut*>* item = astronautsList.getFirst();

	while (item != nullptr)
	{
		if (physics->GetWorld()->Intersection(body, item->data->GetBody()))
		{
			DeleteAstronaut(item->data->GetBody(), physics);
			return true;
		}
		item = item->next;
	}

	return false;
}

bool AstronautManager::CheckCollision(SDL_Rect rect, Physics* physics)
{
	p2List_item<Astronaut*>* item = astronautsList.getFirst();

	while (item != nullptr)
	{
		if (physics->GetWorld()->Intersection(rect, item->data->GetBody()))
		{
			DeleteAstronaut(item->data->GetBody(), physics);
			return true;
		}
		item = item->next;
	}
	return false;
}