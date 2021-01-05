#pragma once

#include "Module.h"
#include "Astronaut.h"
#include "bhBody.h"
#include "bhVec2.h"

#include "p2List.h"

class SDL_Texture;

class AstronautManager : public Module
{
public:
	AstronautManager(App* app, bool start_enabled = true);
	~AstronautManager(){}

	bool Start() override;
	update_status Update(float dt) override;
	update_status PostUpdate() override;
	bool CleanUp() override;
	void Draw();

	Astronaut* CreateAstronaut(int radius, bhVec2 initialPos);
	void DeleteAstronaut(Astronaut* astronaut);
	void DeleteAstronaut(bhBody* astronaut);

private:

	p2List<Astronaut*> astronautsList;
	
	SDL_Texture* astronautTexture;
};