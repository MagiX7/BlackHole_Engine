#include "App.h"
#include "Physics.h"
#include "Asteroid.h"
#include "Physics.h"

#include "Animation.h"

Asteroid::Asteroid()
{
	dieAnim.PushBack({ 0,0,40,40 });
	dieAnim.PushBack({ 40,0,40,40 });
	dieAnim.PushBack({ 80,0,40,40 });
	dieAnim.PushBack({ 120,0,40,40 });
	dieAnim.PushBack({ 160,0,40,40 });

	dieAnim.loop = false;
	dieAnim.speed = 5.0f;
}

Asteroid::~Asteroid()
{
}

bool Asteroid::Start()
{
	body->SetLinearVelocity(bhVec2(1.5f, 0.0f));

	return true;
}

bool Asteroid::Update(float dt)
{
	if (METERS_TO_PIXELS(body->GetPosition().x) > SCREEN_WIDTH || METERS_TO_PIXELS(body->GetPosition().x) < 0)
		body->SetLinearVelocity(-body->GetLinearVelocity().x, body->GetLinearVelocity().y);

	body->SetLinearVelocity(body->GetLinearVelocity().x, body->GetLinearVelocity().y);

	if (die) dieAnim.Update(dt);

	return true;
}

bool Asteroid::CleanUp()
{
	return true;
}

void Asteroid::SetBody(bhBody* body)
{
	this->body = body;
}