#include "App.h"
#include "Module.h"
#include "Astronaut.h"

Astronaut::Astronaut()
{
}

Astronaut::~Astronaut()
{
}

bool Astronaut::Start()
{
	speedX = 1.5f;
	speedY = 1.5f;
	body->SetLinearVelocity(speedX, speedY);

	return true;
}

bool Astronaut::Update(float dt)
{
	body->SetPosition(bhVec2(body->GetPosition().x + (double)speedX * dt, body->GetPosition().y + (double)speedY * dt));
	body->SetBodyAngle(body->GetBodyAngle() + (double)2.0f * dt);

	if (METERS_TO_PIXELS(body->GetPosition().y) > METERS_TO_PIXELS(initialPos.y + 100.0f) || METERS_TO_PIXELS(body->GetPosition().y) < METERS_TO_PIXELS(initialPos.y - 100.0f))
		speedY = -speedY;

	if (METERS_TO_PIXELS(body->GetPosition().x) > SCREEN_WIDTH || METERS_TO_PIXELS(body->GetPosition().x) < 0)
		speedX = -speedX;

	LOG("POS X %f", METERS_TO_PIXELS(body->GetPosition().x));
	LOG("POS X %f", METERS_TO_PIXELS(initialPos.x));

	return true;
}

void Astronaut::Draw()
{

}

bool Astronaut::CleanUp()
{
	return true;
}

void Astronaut::SetBody(bhBody* body)
{
	this->body = body;
}

void Astronaut::SetInitialPos(bhVec2 initialPos)
{
	this->initialPos = initialPos;
}
