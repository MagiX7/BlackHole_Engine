#include "Asteroid.h"
#include "Physics.h"

Asteroid::Asteroid()
{
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