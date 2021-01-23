#include "App.h"
#include "Render.h"
#include "SceneManager.h"
#include "SceneGameplay.h"
#include "SceneTitle.h"
#include "SceneDead.h"

#define FADEOUT_TRANSITION_SPEED	2.0f
#define FADEIN_TRANSITION_SPEED		2.0f

SceneManager::SceneManager(App* parent, bool startEnabled) : Module(parent, startEnabled)
{
	onTransition = false;
	fadeOutCompleted = false;
	transitionAlpha = 0.0f;
}

SceneManager::~SceneManager()
{
	app->tex->UnLoad(texture);
}

bool SceneManager::Start()
{
	bool ret = true;

	current = new SceneTitle();
	current->Load(app->tex);

	next = nullptr;

	texture = app->tex->Load("Assets/Textures/bg.png");

	return ret;
}

update_status SceneManager::Update(float dt)
{
	update_status ret = update_status::UPDATE_CONTINUE;

	// Move the camera up
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		app->render->camera.y += floor(200.0f * dt);
	}

	// Move the camera down
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		app->render->camera.y -= floor(200.0f * dt);
	}

	// Move the camera to the left
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		app->render->camera.x += floor(200.0f * dt);
	}

	// Move the camera to the right
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		app->render->camera.x -= floor(200.0f * dt);
	}

	if (!onTransition)
	{
		ret = current->Update(app->input, dt);
	}
	else
	{
		if (!fadeOutCompleted)
		{
			transitionAlpha += (FADEOUT_TRANSITION_SPEED * dt);

			// NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
			// For that reason we compare against 1.01f, to avoid last frame loading stop
			if (transitionAlpha > 1.01f)
			{
				transitionAlpha = 1.0f;

				current->Unload(app->tex);	// Unload current screen
				next->Load(app->tex);	// Load next screen

				current = nullptr;	// Free current pointer
				current = next;		// Assign next pointer
				next = nullptr;

				// Activate fade out effect to next loaded screen
				fadeOutCompleted = true;
			}
		}
		else  // Transition fade out logic
		{
			transitionAlpha -= (FADEIN_TRANSITION_SPEED * dt);

			if (transitionAlpha < -0.01f)
			{
				transitionAlpha = 0.0f;
				fadeOutCompleted = false;
				onTransition = false;
			}
		}
	}

	// Draw current scene
	ret = current->Draw(app->render);

	// Draw full screen rectangle in front of everything
	if (onTransition)
	{
		app->render->DrawQuad({ -app->render->camera.x, -app->render->camera.y, 1024, 900 }, 0, 0, 0, (unsigned char)(255.0f * transitionAlpha));
	}

	if (current->transitionRequired)
	{
		onTransition = true;
		fadeOutCompleted = false;
		transitionAlpha = 0.0f;

		switch (current->nextScene)
		{
		case SceneType::INTRO: next = new SceneTitle(); break;
		case SceneType::GAMEPLAY: next = new SceneGameplay(app); break;
		case SceneType::ENDING: next = new SceneDead(); break;
		default: break;
		}

		current->transitionRequired = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) ret = update_status::UPDATE_STOP;

	return ret;
}

update_status SceneManager::PostUpdate()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	return ret;
}

bool SceneManager::CleanUp()
{
	bool ret = true;

	LOG("Unloading Scene Manager");
	
	if (current != nullptr) ret = current->Unload(app->tex);

	return ret;
}