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
	earth = app->physics->CreateBody("earth", BodyType::STATIC);
	earth->SetRadius(PIXEL_TO_METERS(1000));
	int x = SCREEN_WIDTH / 2;
	int y = 1250 + 2 * earth->GetBodyRadius();
	earth->SetPosition(bhVec2(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y)));


	moon = app->physics->CreateBody("moon", BodyType::STATIC);
	moon->SetRadius(PIXEL_TO_METERS(800));
	y = -12895;
	moon->SetPosition(bhVec2(PIXEL_TO_METERS(x + 0.8f), PIXEL_TO_METERS(y)));

	//astronaut = app->physics->CreateBody("astronaut");
	//astronaut->SetRadius(PIXEL_TO_METERS(15));
	//astronaut->SetPosition(bhVec2(PIXEL_TO_METERS(700), PIXEL_TO_METERS(0)));
	//astronautTexture = app->tex->Load("Assets/Textures/astronaut.png");

	app->astronautManager->CreateAstronaut(15, bhVec2(700, -20));
	app->astronautManager->CreateAstronaut(15, bhVec2(400, -1000));
	app->astronautManager->CreateAstronaut(15, bhVec2(550, -1500));
	app->astronautManager->CreateAstronaut(15, bhVec2(700, -3000));
	app->astronautManager->CreateAstronaut(15, bhVec2(650, -4000));
	app->astronautManager->CreateAstronaut(15, bhVec2(660, -5000));
	app->astronautManager->CreateAstronaut(15, bhVec2(700, -6000));
	app->astronautManager->Start();

	app->asteroidManager->CreateAsteroid(20.5f, bhVec2(500, -800));
	app->asteroidManager->CreateAsteroid(20.5f, bhVec2(300, -1400));
	app->asteroidManager->CreateAsteroid(20.5f, bhVec2(700, -2000));
	app->asteroidManager->CreateAsteroid(20.5f, bhVec2(500, -2600));
	app->asteroidManager->CreateAsteroid(20.5f, bhVec2(300, -3200));
	app->asteroidManager->CreateAsteroid(20.5f, bhVec2(700, -3800));

	app->asteroidManager->Start();

	bg = app->tex->Load("Assets/Textures/bg.png");
	app->audio->PlayMusic("Assets/Audio/earth_scene.ogg");

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

	app->render->DrawQuad(SDL_Rect{ 0,-800, 2000, 2 }, 255, 0, 0);
		
	app->render->DrawCircle(METERS_TO_PIXELS(earth->GetPosition().x), METERS_TO_PIXELS(earth->GetPosition().y), METERS_TO_PIXELS(earth->GetBodyRadius()), 255, 0, 0);
	app->render->DrawCircle(METERS_TO_PIXELS(moon->GetPosition().x), METERS_TO_PIXELS(moon->GetPosition().y), METERS_TO_PIXELS(moon->GetBodyRadius()), 255, 0, 0);
	
	return update_status::UPDATE_CONTINUE;
}

bool Scene::CleanUp()
{
	app->tex->UnLoad(bg);
	app->astronautManager->CleanUp();
	app->asteroidManager->CleanUp();
	
	delete earth;
	delete moon;

	return true;
}