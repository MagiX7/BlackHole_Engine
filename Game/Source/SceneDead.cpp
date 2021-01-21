#include "Input.h"
#include "Texture.h"
#include "Render.h"

#include "SceneDead.h"

SceneDead::SceneDead()
{
	animFire.PushBack({ 4,16,32,84 });
	animFire.PushBack({ 44,16,32,84 });
	animFire.PushBack({ 84,20,32,80 });
	animFire.PushBack({ 124,12,32,88 });
	animFire.PushBack({ 160,16,40,84 });
	animFire.PushBack({ 204,20,32,80 });
	animFire.PushBack({ 244,20,36,84 });
	animFire.PushBack({ 284,16,36,84 });
	animFire.PushBack({ 324,24,36,84 });
	animFire.PushBack({ 364,20,36,80 });
	animFire.loop = true;
}

SceneDead::~SceneDead()
{
}

bool SceneDead::Load(Texture* tex, SDL_Texture* t)
{
	bg = tex->Load("Assets/Textures/lose.png");
	textureFire = tex->Load("Assets/Textures/Fires/fire2.png");

	return true;
}

update_status SceneDead::Update(Input* input, float dt)
{
	update_status ret = update_status::UPDATE_CONTINUE;

	animFire.speed = 300.0f * dt;

	if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		TransitionToScene(SceneType::INTRO);

	if (input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = update_status::UPDATE_STOP;

	animFire.Update(dt);

	return ret;
}

update_status SceneDead::Draw(Render* ren)
{
	ren->DrawTexture(bg, 0, -ren->camera.y, NULL);

	ren->DrawTexture(textureFire, 547, -ren->camera.y + 380, &animFire.GetCurrentFrame());
	ren->DrawTexture(textureFire, 417, -ren->camera.y + 420, &animFire.GetCurrentFrame(), 1.0f, -20, 0, 0);

	return update_status::UPDATE_CONTINUE;
}

bool SceneDead::UnLoad(Texture* tex)
{
	tex->UnLoad(bg);
	tex->UnLoad(textureFire);

	return true;
}
