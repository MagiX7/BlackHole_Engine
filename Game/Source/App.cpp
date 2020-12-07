#include "App.h"

App::App()
{
	window = new Window(this);
	input = new Input(this);
	audio = new Audio(this);
	//scene_intro = new ModuleSceneIntro(this);
	render = new Render(this);
	//camera = new ModuleCamera3D(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(input);
	AddModule(audio);
	//AddModule(camera);

	// Scenes
	//AddModule(scene_intro);


	AddModule(render);
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

	return ret;
}


// ---------------------------------------------
void App::PrepareUpdate()
{
}

// ---------------------------------------------
void App::FinishUpdate()
{
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status App::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();

	p2List_item<Module*>* item = list_modules.getFirst();

	while (item != NULL && ret == UPDATE_CONTINUE)
	{
		ret = item->data->PreUpdate();
		item = item->next;
	}

	item = list_modules.getFirst();

	while (item != NULL && ret == UPDATE_CONTINUE)
	{
		ret = item->data->Update();
		item = item->next;
	}

	item = list_modules.getFirst();

	while (item != NULL && ret == UPDATE_CONTINUE)
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