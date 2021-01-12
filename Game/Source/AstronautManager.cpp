#include "App.h"
#include "Texture.h"
#include "AstronautManager.h"
#include "Physics.h"



AstronautManager::AstronautManager(App* app, bool start_enabled): Module(app, start_enabled)
{

}

bool AstronautManager::Start()
{
	astronautTexture = app->tex->Load("Assets/Textures/astronaut.png");
	
	p2List_item<Astronaut*>* item = astronautsList.getFirst();

	while (item != nullptr)
	{
		item->data->Start();

		item = item->next;
	}



	return true;
}


update_status AstronautManager::Update(float dt)
{
	p2List_item<Astronaut*>* item = astronautsList.getFirst();

	while (item != nullptr)
	{
		item->data->Update(dt);

		item = item->next;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status AstronautManager::PostUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

bool AstronautManager::CleanUp()
{
	p2List_item<Astronaut*>* item = astronautsList.getFirst();

	while (item != nullptr)
	{
		item->data->CleanUp();

		item = item->next;
	}
	
	app->tex->UnLoad(astronautTexture);

	return false;
}

void AstronautManager::Draw()
{
	p2List_item<Astronaut*>* item = astronautsList.getFirst();

	while (item != nullptr)
	{
		app->render->DrawTexture(item->data->texture, METERS_TO_PIXELS(item->data->GetBody()->GetPosition().x - 15), METERS_TO_PIXELS(item->data->GetBody()->GetPosition().y - 15), NULL, 1.0f, item->data->GetBody()->GetBodyAngle() * 180 / M_PI);
		app->render->DrawCircle(METERS_TO_PIXELS(item->data->GetBody()->GetPosition().x), METERS_TO_PIXELS(item->data->GetBody()->GetPosition().y), METERS_TO_PIXELS(item->data->GetBody()->GetBodyRadius()), 255, 0, 0);
		
		item = item->next;
	}
}

Astronaut* AstronautManager::CreateAstronaut(int radius, bhVec2 initialPos)
{
	Astronaut* astronaut = new Astronaut();
	bhBody* astronautBody = app->physics->CreateBody("astronaut", BodyType::NO_GRAVITY);
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

void AstronautManager::DeleteAstronaut(Astronaut* astronaut)
{
	p2List_item<Astronaut*>* item = astronautsList.getFirst();

	while (item != nullptr)
	{
		if (item->data == astronaut)
		{
			app->physics->DestroyBody(item->data->GetBody());
			delete item->data;
			astronautsList.del(item);
		}

		item = item->next;
	}

}

void AstronautManager::DeleteAstronaut(bhBody* astronaut)
{
	p2List_item<Astronaut*>* item = astronautsList.getFirst();

	while (item != nullptr)
	{
		if (item->data->GetBody() == astronaut)
		{
			app->physics->DestroyBody(item->data->GetBody());
			delete item->data;
			astronautsList.del(item);
		}

		item = item->next;
	}
}
