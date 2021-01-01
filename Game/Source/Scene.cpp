#include "App.h"
#include "Texture.h"

#include "bhBody.h"
#include "Scene.h"


Scene::Scene(App* parent, bool startEnabled) : Module(parent, startEnabled)
{
}

Scene::~Scene()
{
}

bool Scene::Start()
{
	floor = app->physics->CreateBody("floor");
	floor->SetRadius(PIXEL_TO_METERS(1000));
	int x = SCREEN_WIDTH / 2;
	int y = 1550 + 2 * floor->GetBodyRadius();
	floor->SetPosition(bhVec2(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y)));
	//floor->SetPosition(bhVec2(PIXEL_TO_METERS(0), PIXEL_TO_METERS(1000)));

	/*floor2 = app->physics->CreateBody("top");
	floor2->SetPosition(bhVec2(0, 0));
	floor2->SetRadius(PIXEL_TO_METERS(1000));*/

	bg = app->tex->Load("Assets/Textures/bg.png");

	return true;
}

update_status Scene::PreUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

update_status Scene::Update(float dt)
{
	app->physics->Step(dt);

	LOG("==========================");
	LOG("%f  %f", floor->GetPosition().x, floor->GetPosition().y);

	return update_status::UPDATE_CONTINUE;
}

update_status Scene::PostUpdate()
{
	app->render->DrawTexture(bg, 0, -5200, NULL);
	app->spaceship->Draw();
	
	//int r = floor->GetBodyRadius();
	//int x = METERS_TO_PIXELS(floor->GetPosition().x);
	//int y = METERS_TO_PIXELS(floor->GetPosition().y);
	
	app->render->DrawCircle(METERS_TO_PIXELS(floor->GetPosition().x), METERS_TO_PIXELS(floor->GetPosition().y), METERS_TO_PIXELS(floor->GetBodyRadius()), 255, 0, 0);
	
	
	//app->render->DrawQuad({ (int)floor->GetPosition().x, (int)floor->GetPosition().y, 1024, 50 }, 255, 0, 0);
	//app->render->DrawQuad({ (int)floor2->GetPosition().x, (int)floor2->GetPosition().y, 1024, 50 }, 255, 0, 0);

	return update_status::UPDATE_CONTINUE;
}

bool Scene::CleanUp()
{
	return true;
}