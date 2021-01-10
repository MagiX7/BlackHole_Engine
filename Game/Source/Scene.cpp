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
	floor = app->physics->CreateBody("floor", BodyType::STATIC);
	floor->SetRadius(PIXEL_TO_METERS(1000));
	int x = SCREEN_WIDTH / 2;
	int y = 1250 + 2 * floor->GetBodyRadius();
	floor->SetPosition(bhVec2(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y)));

	app->audio->PlayMusic("Assets/Audio/earth_scene.ogg");

	/*floor2 = app->physics->CreateBody("top");
	floor2->SetPosition(bhVec2(0, 0));
	floor2->SetRadius(PIXEL_TO_METERS(1000));*/

	/*astronaut = app->physics->CreateBody("astronaut");
	astronaut->SetRadius(PIXEL_TO_METERS(15));
	astronaut->SetPosition(bhVec2(PIXEL_TO_METERS(700), PIXEL_TO_METERS(0)));
	astronautTexture = app->tex->Load("Assets/Textures/astronaut.png");*/

	app->astronautManager->CreateAstronaut(15, bhVec2(700, -20));
	app->astronautManager->CreateAstronaut(15, bhVec2(400, -1000));
	app->astronautManager->CreateAstronaut(15, bhVec2(550, -1500));
	app->astronautManager->CreateAstronaut(15, bhVec2(700, -3000));
	app->astronautManager->CreateAstronaut(15, bhVec2(650, -4000));
	app->astronautManager->CreateAstronaut(15, bhVec2(660, -5000));
	app->astronautManager->CreateAstronaut(15, bhVec2(700, -6000));

	app->astronautManager->Start();

	bg = app->tex->Load("Assets/Textures/bg.png");

	app->asteroidManager->CreateAsteroid(20.5f, bhVec2(500, -800));

	app->asteroidManager->Start();

	return true;
}

update_status Scene::PreUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

update_status Scene::Update(float dt)
{
	//LOG("==========================");

	//LOG("MUNDO %f  %f", floor->GetPosition().x, floor->GetPosition().y);

	return update_status::UPDATE_CONTINUE;
}

update_status Scene::PostUpdate()
{
	app->render->DrawTexture(bg, 0, -12500, NULL);
	app->spaceship->Draw();
	app->astronautManager->Draw();
	app->asteroidManager->Draw();
	//app->render->DrawTexture(astronautTexture, METERS_TO_PIXELS(astronaut->GetPosition().x - 14), METERS_TO_PIXELS(astronaut->GetPosition().y - 15), NULL, 1.0f, astronaut->GetBodyAngle());
	
	int r = floor->GetBodyRadius();
	int x = METERS_TO_PIXELS(floor->GetPosition().x);
	int y = METERS_TO_PIXELS(floor->GetPosition().y);
	
	app->render->DrawCircle(METERS_TO_PIXELS(floor->GetPosition().x), METERS_TO_PIXELS(floor->GetPosition().y), METERS_TO_PIXELS(floor->GetBodyRadius()), 255, 0, 0);
	
	//app->render->DrawCircle(METERS_TO_PIXELS(astronaut->GetPosition().x), METERS_TO_PIXELS(astronaut->GetPosition().y), METERS_TO_PIXELS(astronaut->GetBodyRadius()), 255, 0, 0);
	
	//app->render->DrawQuad({ (int)floor->GetPosition().x, (int)floor->GetPosition().y, 1024, 50 }, 255, 0, 0);
	//app->render->DrawQuad({ (int)floor2->GetPosition().x, (int)floor2->GetPosition().y, 1024, 50 }, 255, 0, 0);

	return update_status::UPDATE_CONTINUE;
}

bool Scene::CleanUp()
{
	return true;
}