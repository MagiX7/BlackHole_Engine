#include "App.h"

App::App()
{
	PERF_START(pTimer);

	window = new Window(this);
	input = new Input(this);
	audio = new Audio(this);
	scene = new Scene(this);
	render = new Render(this);
	tex = new Texture(this);
	spaceship = new Spaceship(this);
	physics = new PhysicsEngine(this);
	//camera = new ModuleCamera3D(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(input);
	AddModule(audio);
	AddModule(tex);
	AddModule(spaceship);
	AddModule(scene);
	//AddModule(camera);

	// Scenes


	AddModule(render);

	cappedMs = 1000 / 60;

	PERF_PEEK(pTimer);
}

App::~App()
{
	p2List_item<Module*>* item = list_modules.getLast();

	while (item != NULL)
	{
		delete item->data;
		item = item->prev;
	}
}

bool App::Init()
{
	PERF_START(pTimer);

	bool ret = true;

	// Call Init() in all modules
	p2List_item<Module*>* item = list_modules.getFirst();

	while (item != NULL && ret == true)
	{
		ret = item->data->Init();
		item = item->next;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.getFirst();

	while (item != NULL && ret == true)
	{
		ret = item->data->Start();
		item = item->next;
	}

	PERF_PEEK(pTimer);

	return ret;
}


// ---------------------------------------------
void App::PrepareUpdate()
{
	frameCount++;
	lastSecFrameCount++;

	// Calculate the differential time since last frame
	dt = frameTime.ReadSec();
	frameTime.Start();
}

// ---------------------------------------------
void App::FinishUpdate()
{
	if (lastSecFrameTime.Read() > 1000)
	{
		lastSecFrameTime.Start();
		prevLastSecFrameCount = lastSecFrameCount;
		lastSecFrameCount = 0;
	}

	float averageFps = float(frameCount) / startupTime.ReadSec();
	float secondsSinceStartup = startupTime.ReadSec();
	uint lastFrameMs = frameTime.Read();
	uint framesOnLastUpdate = prevLastSecFrameCount;

	static char title[256];
	sprintf_s(title, 256, "FPS: %i / Avg. FPS: %.2f / Last-frame MS: %02u ",
		framesOnLastUpdate, averageFps, lastFrameMs);

	window->SetTitle(title);

	if ((cappedMs > 0) && (lastFrameMs < cappedMs))
	{
		PerfTimer pt;
		SDL_Delay(cappedMs - lastFrameMs);
		//LOG("We waited for %i ms and got back in %f", cappedMs - lastFrameMs, pt.ReadMs());
	}
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status App::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;
	PrepareUpdate();

	p2List_item<Module*>* item = list_modules.getFirst();

	while (item != NULL && ret == update_status::UPDATE_CONTINUE)
	{
		ret = item->data->PreUpdate();
		item = item->next;
	}

	item = list_modules.getFirst();

	while (item != NULL && ret == update_status::UPDATE_CONTINUE)
	{
		ret = item->data->Update(dt);
		item = item->next;
	}

	item = list_modules.getFirst();

	while (item != NULL && ret == update_status::UPDATE_CONTINUE)
	{
		ret = item->data->PostUpdate();
		item = item->next;
	}

	FinishUpdate();
	return ret;
}

bool App::CleanUp()
{
	bool ret = true;
	p2List_item<Module*>* item = list_modules.getLast();

	while (item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}
	return ret;
}

void App::AddModule(Module* mod)
{
	list_modules.add(mod);
}