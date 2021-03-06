#pragma once

#include "p2List.h"
#include "Globals.h"
#include "Timer.h"
#include "PerfTimer.h"
#include "Module.h"
#include "Window.h"
#include "Input.h"
#include "Fonts.h"
#include "Audio.h"
#include "SceneManager.h"
#include "Render.h"
#include "Texture.h"
#include "Physics.h"

class App
{
public:
	Window* window;
	Input* input;
	Audio* audio;
	SceneManager* sceneManager;
	Render* render;
	Texture* tex;
	Physics* physics;
	Fonts* fonts;

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

	PerfTimer pTimer;
	uint64 frameCount = 0;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;
	uint32 lastSecFrameCount = 0;
	uint32 prevLastSecFrameCount = 0;
	float dt = 0.0f;

	int cappedMs = -1;
};