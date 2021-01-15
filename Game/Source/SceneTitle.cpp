#include "App.h"
#include "Texture.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle()
{
	bg = nullptr;
}

SceneTitle::~SceneTitle()
{
}

bool SceneTitle::Load(Texture* tex, SDL_Texture* texture)
{
	LOG("Loading Title Scene");

	bg = tex->Load("Assets/Textures/title.png");

	return true;
}

update_status SceneTitle::Update(Input* input, float dt)
{
	if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) TransitionToScene(SceneType::GAMEPLAY);

	return update_status::UPDATE_CONTINUE;
}

update_status SceneTitle::Draw(Render* ren)
{
	ren->DrawTexture(bg, -ren->camera.x, -ren->camera.y, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneTitle::Unload(Texture* tex)
{
	LOG("Unloading Title Scene");

	tex->UnLoad(bg);

	return true;
}