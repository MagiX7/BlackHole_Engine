#include "App.h"

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
	floor = new bhBody;
	floor->SetPosition(bhVec2(0,718));

	return true;
}

update_status Scene::PreUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

update_status Scene::Update()
{
	return update_status::UPDATE_CONTINUE;
}

update_status Scene::PostUpdate()
{
	app->render->DrawQuad({ (int)floor->GetPosition().x, (int)floor->GetPosition().y, 1024, 50 }, 255, 0, 0);

	return update_status::UPDATE_CONTINUE;
}

bool Scene::CleanUp()
{
	return true;
}
