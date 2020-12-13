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
	floor->SetPosition(bhVec2(0, 718));
	floor->SetRadius(10);
	floor2 = app->physics->CreateBody("top");
	floor2->SetPosition(bhVec2(0, 0));
	floor2->SetRadius(10);

	bg = app->tex->Load("Assets/Textures/bg.png");

	return true;
}

update_status Scene::PreUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

update_status Scene::Update(float dt)
{
	//LOG("%f  %f", app->spaceship->GetBody()->GetPosition().x, app->spaceship->GetBody()->GetPosition().x);

	return update_status::UPDATE_CONTINUE;
}

update_status Scene::PostUpdate()
{
	app->render->DrawTexture(bg, 0, -5200, NULL);
	app->spaceship->Draw();

	app->render->DrawQuad({ (int)floor->GetPosition().x, (int)floor->GetPosition().y, 1024, 50 }, 255, 0, 0);
	//app->render->DrawQuad({ (int)floor2->GetPosition().x, (int)floor2->GetPosition().y, 1024, 50 }, 255, 0, 0);

	return update_status::UPDATE_CONTINUE;
}

bool Scene::CleanUp()
{
	return true;
}
