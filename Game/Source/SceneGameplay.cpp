#include "App.h"
#include "Texture.h"
#include "Scene.h"
#include "Spaceship.h"
#include "AsteroidManager.h"
#include "AstronautManager.h"

#include "bhBody.h"
#include "SceneGameplay.h"


SceneGameplay::SceneGameplay(App* parent)
{
	this->app = parent;
}

SceneGameplay::~SceneGameplay()
{
}

bool SceneGameplay::Load(Texture* tex)
{
	spaceship = new Spaceship(app, this);
	spaceship->Start();

	moon = app->physics->CreateBody("moon", BodyType::STATIC);
	moon->SetRadius(PIXEL_TO_METERS(800));
	int x = SCREEN_WIDTH / 2;
	int y = -12895;
	moon->SetPosition(bhVec2(PIXEL_TO_METERS(x + 0.8f), PIXEL_TO_METERS(y)));
	moon->SetActive(true);
	
	astronautManager = new AstronautManager();
	astronautManager->SetTexture(tex);

	astronautManager->CreateAstronaut(15, bhVec2(700, -2400), app->physics);
	astronautManager->CreateAstronaut(15, bhVec2(400, -3200), app->physics);
	astronautManager->CreateAstronaut(15, bhVec2(550, -4000), app->physics);
	astronautManager->CreateAstronaut(15, bhVec2(700, -4800), app->physics);
	astronautManager->CreateAstronaut(15, bhVec2(650, -5600), app->physics);
	astronautManager->CreateAstronaut(15, bhVec2(660, -6400), app->physics);
	astronautManager->CreateAstronaut(15, bhVec2(400, -7200), app->physics);
	astronautManager->CreateAstronaut(15, bhVec2(600, -8000), app->physics);
	astronautManager->CreateAstronaut(15, bhVec2(500, -8800), app->physics);
	astronautManager->CreateAstronaut(15, bhVec2(100, -9600), app->physics);
	astronautManager->CreateAstronaut(15, bhVec2(800, -10500), app->physics);
	astronautManager->CreateAstronaut(15, bhVec2(500, -11000), app->physics);
	

	astronautManager->Start();

	asteroidManager = new AsteroidManager();
	asteroidManager->SetTexture(tex);

	asteroidManager->CreateAsteroid(20.5f, bhVec2(500, -3000), app->physics);
	asteroidManager->CreateAsteroid(20.5f, bhVec2(300, -3500), app->physics);
	asteroidManager->CreateAsteroid(20.5f, bhVec2(700, -4500), app->physics);
	asteroidManager->CreateAsteroid(20.5f, bhVec2(500, -4700), app->physics);
	asteroidManager->CreateAsteroid(20.5f, bhVec2(700, -5500), app->physics);
	asteroidManager->CreateAsteroid(20.5f, bhVec2(500, -6000), app->physics);
	asteroidManager->CreateAsteroid(20.5f, bhVec2(300, -7000), app->physics);
	asteroidManager->CreateAsteroid(20.5f, bhVec2(200, -7700), app->physics);
	asteroidManager->CreateAsteroid(20.5f, bhVec2(500, -8500), app->physics);
	asteroidManager->CreateAsteroid(20.5f, bhVec2(300, -9300), app->physics);
	asteroidManager->CreateAsteroid(20.5f, bhVec2(200, -10200), app->physics);
	asteroidManager->CreateAsteroid(20.5f, bhVec2(600, -10900), app->physics);
	asteroidManager->CreateAsteroid(20.5f, bhVec2(400, -11200), app->physics);

	asteroidManager->Start();

	waterDropFx = app->audio->LoadFx("Assets/Audio/waterdrop_1.wav");
	waterDropPlayOnce = false;

	bgTop = tex->Load("Assets/Textures/bg_top.png");
	bgBottom = tex->Load("Assets/Textures/bg_bottom.png");

	app->audio->PlayMusic("Assets/Audio/earth_scene.ogg");

	app->render->camera.y = 12500;
	arriveMoon = false;
	arriveWater = false;

	return true;
}

update_status SceneGameplay::Update(Input* input, float dt)
{
	spaceship->Update(dt, asteroidManager, astronautManager);

	if (app->physics->GetWorld()->Intersection(spaceship->GetBody(),moon) && spaceship->GetBody()->GetLinearVelocity().y <= 0.2f)
	{
		if (spaceship->GetFuel() <= 100.0f)
			spaceship->AddFuel(1.2f * dt);
	}

	asteroidManager->Update(dt);
	astronautManager->Update(dt);

	app->render->camera.y = METERS_TO_PIXELS(-spaceship->GetBody()->GetPosition().y) + (SCREEN_HEIGHT / 2 + app->render->offset);

	app->render->camera.x = 0;

	if (spaceship->GetBody()->GetLinearVelocity().y < 0)
	{
		if (app->render->offset < 200) app->render->offset += 150 * dt;
	}

	if (spaceship->GetBody()->GetLinearVelocity().y > 0)
	{
		if (app->render->offset > -200) app->render->offset -= 150 * dt;
	}

	if (!spaceship->GetBody()->IsActive()) TransitionToScene(SceneType::ENDING);

	if (arriveMoon && arriveWater) TransitionToScene(SceneType::WIN);

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) TransitionToScene(SceneType::ENDING);

	// Camera ========================================

	if (app->render->camera.y <= 400) 
		app->render->camera.y = 400;
	if (app->render->camera.y >= 12500) 
		app->render->camera.y = 12500;

	// FX ============================================

	if (spaceship->GetBody()->GetPosition().y >= PIXEL_TO_METERS(248) && waterDropPlayOnce == false)
	{
		app->audio->PlayFx(waterDropFx);
		waterDropPlayOnce = true;
		arriveWater = true;
	}
	else if (spaceship->GetBody()->GetPosition().y + spaceship->GetBody()->GetBodyRadius() < PIXEL_TO_METERS(248))
	{
		waterDropPlayOnce = false;
	}

	//LOG("POSITION %d %d=========================================================", app->render->camera.x, app->render->camera.y);

	return update_status::UPDATE_CONTINUE;
}

update_status SceneGameplay::Draw(Render* ren)
{
	ren->DrawTexture(bgTop, 0, -12500, NULL);
	ren->DrawTexture(bgBottom, 0, -6000, NULL);

	astronautManager->Draw(ren);
	asteroidManager->Draw(ren);
	spaceship->Draw();

	ren->DrawCircle(METERS_TO_PIXELS(moon->GetPosition().x), METERS_TO_PIXELS(moon->GetPosition().y), METERS_TO_PIXELS(moon->GetBodyRadius()), 255, 0, 0);
	
	return update_status::UPDATE_CONTINUE;
}

bool SceneGameplay::Unload(Texture* tex)
{
	bool ret = true;
	LOG("Unloading Gameplay Scene");

	tex->UnLoad(bgTop);
	tex->UnLoad(bgBottom);

	ret = astronautManager->CleanUp(tex);
	ret = asteroidManager->CleanUp(tex);
	spaceship->CleanUp();
	app->physics->GetWorld()->CleanUp();
	
	//delete earth;
	delete moon;
	delete spaceship;
	delete astronautManager;
	delete asteroidManager;

	return true;
}