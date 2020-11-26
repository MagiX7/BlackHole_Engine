#ifndef __Window_H__
#define __Window_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class App;

class Window : public Module
{
public:

	Window(App* app, bool start_enabled = true);

	// Destructor
	virtual ~Window();

	bool Init();
	bool CleanUp();

	void SetTitle(const char* title);

public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;
};

#endif // __Window_H__