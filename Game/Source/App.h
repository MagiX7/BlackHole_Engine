#pragma once

#include "p2List.h"
#include "Globals.h"
//#include "Timer.h"
#include "Module.h"
#include "Window.h"
//#include "Input.h"
//#include "Audio.h"
//#include "SceneIntro.h"
//#include "Renderer3D.h"
//#include "Camera3D.h"

class App
{
public:
	Window* window;
	//Input* input;
	//Audio* audio;
	//SceneIntro* scene_intro;
	//Renderer3D* renderer3D;
	//Camera3D* camera;

private:

	p2List<Module*> list_modules;

public:

	App();
	~App();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};