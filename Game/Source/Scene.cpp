#include "App.h"
#include "Texture.h"
#include "Scenes.h"
#include "Spaceship.h"
#include "AsteroidManager.h"
#include "AstronautManager.h"

#include "bhBody.h"
#include "Scene.h"


Scene::Scene(App* parent)
{
	this->app = parent;
}

Scene::~Scene()
{
}

bool Scene::Load(Texture* tex, SDL_Texture* texture)
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

	spaceship = new Spaceship(app, this);
	spaceship->Start();
	
	astronautManager = new AstronautManager();
	astronautManager->SetTexture(tex);

	astronautManager->CreateAstronaut(15, bhVec2(700, -20), app->physics);
	astronautManager->CreateAstronaut(15, bhVec2(400, -1000), app->physics);
	astronautManager->CreateAstronaut(15, bhVec2(550, -1500), app->physics);
	astronautManager->CreateAstronaut(15, bhVec2(700, -3000), app->physics);
	astronautManager->CreateAstronaut(15, bhVec2(650, -4000), app->physics);
	astronautManager->CreateAstronaut(15, bhVec2(660, -5000), app->physics);
	astronautManager->CreateAstronaut(15, bhVec2(700, -6000), app->physics);

	astronautManager->Start();

	asteroidManager = new AsteroidManager();
	asteroidManager->SetTexture(tex);

	//asteroidManager->CreateAsteroid(20.5f, bhVec2(500, -800), app->physics);
	//asteroidManager->CreateAsteroid(20.5f, bhVec2(300, -1400), app->physics);
	//asteroidManager->CreateAsteroid(20.5f, bhVec2(700, -2000), app->physics);
	//asteroidManager->CreateAsteroid(20.5f, bhVec2(500, -2600), app->physics);
	//asteroidManager->CreateAsteroid(20.5f, bhVec2(300, -3200), app->physics);
	//asteroidManager->CreateAsteroid(20.5f, bhVec2(700, -3800), app->physics);

	asteroidManager->Start();

	bg = texture;
	app->audio->PlayMusic("Assets/Audio/earth_scene.ogg");

	app->render->camera.y = 400;

	return true;
}

update_status Scene::Update(Input* input, float dt)
{
	//LOG("==========================");
	spaceship->Update(dt, asteroidManager, astronautManager);
	asteroidManager->Update(dt);
	astronautManager->Update(dt);
	//LOG("MUNDO %f  %f", floor->GetPosition().x, floor->GetPosition().y);

	app->render->camera.y = METERS_TO_PIXELS(-spaceship->GetBody()->GetPosition().y + SCREEN_HEIGHT / 2 + app->render->offset);

	app->render->camera.x = 0;

	if (spaceship->GetBody()->GetLinearVelocity().y < 0)
	{
		if (app->render->offset < 200) app->render->offset += 150 * dt;
	}

	if (spaceship->GetBody()->GetLinearVelocity().y > 0)
	{
		if (app->render->offset > -200) app->render->offset -= 150 * dt;
	}

	if (!spaceship->GetBody()->IsActive()) 
		TransitionToScene(SceneType::INTRO);

	if (app->render->camera.y <= 400) app->render->camera.y = 400;
	if (app->render->camera.y >= 12500) app->render->camera.y = 12500;

	LOG("POSITION %d %d=========================================================", app->render->camera.x, app->render->camera.y);

	return update_status::UPDATE_CONTINUE;
}

update_status Scene::Draw(Render* ren)
{
	ren->DrawTexture(bg, 0, -12500, NULL);
	astronautManager->Draw(ren);
	asteroidManager->Draw(ren);
	spaceship->Draw();

	app->render->DrawQuad(SDL_Rect{ 0,-800, 2000, 2 }, 255, 0, 0);

	ren->DrawCircle(METERS_TO_PIXELS(earth->GetPosition().x), METERS_TO_PIXELS(earth->GetPosition().y), METERS_TO_PIXELS(earth->GetBodyRadius()), 255, 0, 0);
	ren->DrawCircle(METERS_TO_PIXELS(moon->GetPosition().x), METERS_TO_PIXELS(moon->GetPosition().y), METERS_TO_PIXELS(moon->GetBodyRadius()), 255, 0, 0);
	
	return update_status::UPDATE_CONTINUE;
}

bool Scene::Unload(Texture* tex)
{
	bool ret = true;
	LOG("Unloading Gameplay Scene");

	ret = astronautManager->CleanUp(tex);
	ret = asteroidManager->CleanUp(tex);
	
	delete earth;
	delete moon;

	return true;
}