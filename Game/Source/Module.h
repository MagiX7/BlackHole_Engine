#pragma once

#include "Globals.h"

class App;
enum class update_status;

class Module
{
protected:
	bool enabled;

public:
	App* app;

	Module(App* parent, bool start_enabled = true) : app(parent)
	{}

	virtual ~Module()
	{}

	virtual bool Init()
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual update_status PreUpdate()
	{
		return update_status::UPDATE_CONTINUE;
	}

	virtual update_status Update(float dt)
	{
		return update_status::UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate()
	{
		return update_status::UPDATE_CONTINUE;
	}

	virtual bool CleanUp()
	{
		return true;
	}
};