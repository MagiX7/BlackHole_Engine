#pragma once

class App;

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
		return UPDATE_CONTINUE;
	}

	virtual update_status Update()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp()
	{
		return true;
	}
};