#include "Input.h"
#include "Render.h"
#include "Texture.h"
#include "SceneWin.h"

SceneWin::SceneWin()
{
}

SceneWin::~SceneWin()
{
}

bool SceneWin::Load(Texture* tex)
{
	LOG("Loading Win Scene");

	bg = tex->Load("Assets/Textures/win.png");

	return true;
}

update_status SceneWin::Update(Input* input, float dt)
{
	if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) TransitionToScene(SceneType::INTRO);
	
	return update_status::UPDATE_CONTINUE;
}

update_status SceneWin::Draw(Render* ren)
{
	ren->DrawTexture(bg, -ren->camera.x, -ren->camera.y, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneWin::Unload(Texture* tex)
{
	LOG("Unloading Win Scene");

	tex->UnLoad(bg);

	return true;
}