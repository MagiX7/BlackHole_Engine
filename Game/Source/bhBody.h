#pragma once

#include "bhVec2.h"
#include "SString.h"

enum class BodyType
{
	DYNAMIC,
	STATIC,
	NO_GRAVITY,
	SENSOR,
};

class bhBody
{
private:
	SString name;
	bool active;
	bhVec2 position;
	bhVec2 linearV;
	float radius;
	bhVec2 acceleration;
	bhVec2 totalForce;
	float mass;
	float bodyGravity;
	double angle;
	bhVec2 momentum;

public:
	BodyType type;

public:
	// Default constructor that sets all the variables to default
	bhBody(SString n, BodyType t, bool act = true)
	{
		name = n;
		type = t;
		active = act;
		position = bhVec2(0.0f, 0.0f);
		linearV = bhVec2(0.0f, 0.0f);
		acceleration = bhVec2(0.0f, 0.0f);
		totalForce = bhVec2(0.0f, 0.0f);
		mass = 0.0f;
		bodyGravity = 0.0f;
		angle = 0.0f;
		momentum = bhVec2(0.0f, 0.0f);
	}

	virtual ~bhBody() {};

	void AddForce(bhVec2 f)
	{
		totalForce += f;
	}
	
	void ApplyNewtonSecondLaw()
	{
		acceleration = totalForce / mass;
	}


	void ResetForce()
	{
		totalForce.x = 0;
		totalForce.y = 0;
	}

	void AddMomentum(bhVec2 momentum)
	{
		linearV.x += momentum.x / mass;
		linearV.y += momentum.y / mass;
	}

	void AddMomentumWithForce(bhVec2 v)
	{
		bhVec2 momentum = (v * mass);
		totalForce += momentum;
	}

	// Rotate a body. NOTE: ang must be on DEGREES.
	void Rotate(float ang)
	{
		angle += ang * M_PI / 180;
		if (angle >= 360)
			angle = 0;
	}

	bool IsActive() { return active; }

	// ===================================================
	//					Setters
	// ===================================================

	void SetActive(bool act)
	{
		active = act;
	}

	void SetMass(float m)
	{
		mass = m;
	}

	// Set body position 
	void SetPosition(bhVec2 pos)
	{
		position = pos;
	}
	void SetPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	// Set body linear speed
	void SetLinearVelocity(bhVec2 v)
	{
		linearV = v;
	}

	void SetLinearVelocity(float x, float y)
	{
		linearV.x = x;
		linearV.y = y;
	}

	// Set body radius
	void SetRadius(float rad)
	{
		radius = rad;
	}

	void SetBodyAngle(double a)
	{
		angle = a;
	}
	
	void SetAcceleration(bhVec2 acc)
	{
		acceleration.x = acc.x;
		acceleration.y = acc.y;
	}

	// ===================================================
	//					Getters
	// ===================================================

	// Get the body position
	inline bhVec2& GetPosition()
	{
		return position;
	}
	
	// Get the body linear velocity
	inline bhVec2& GetLinearVelocity()
	{
		return linearV;
	}

	// Get the body angular velocity
	inline bhVec2& GetAngularVelocity()
	{
		//return angularV;
	}

	// Get the body acceleration
	inline bhVec2& GetAcceleration()
	{
		return acceleration;
	}

	// Get body mass
	inline float& GetBodyMass()
	{
		return mass;
	}

	//Get gravity on the body;
	inline float& GetBodyGravity()
	{
		return bodyGravity;
	}

	// Get the body angle
	inline double& GetBodyAngle()
	{
		return angle;
	}

	// Get the body radius
	inline float& GetBodyRadius()
	{
		return radius;
	}

	inline SString& GetName()
	{
		return name;
	}

	inline bhVec2& GetTotalForce()
	{
		return totalForce;
	}
};