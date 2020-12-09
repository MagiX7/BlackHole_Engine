#include "App.h"


#include "Scene.h"


Scene::Scene(App* parent, bool startEnabled) : Module(parent, startEnabled)
{
}

Scene::~Scene()
{
}

bool Scene::Start()
{

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

bool Scene::CleanUp()
{
	return true;
}
