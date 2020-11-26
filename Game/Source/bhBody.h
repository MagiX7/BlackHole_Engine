#pragma once

#include "bhVec2.h"

class bhBody
{
private:
	bhVec2 position;
	bhVec2 linearV;
	float angularV;
	bhVec2 acceleration;
	bhVec2 force;
	float mass;
	float bodyGravity;
	float angle;

public:
	// Default constructor that sets all the variables to default
	bhBody()
	{
		position = bhVec2(0.0f, 0.0f);
		linearV = bhVec2(0.0f, 0.0f);
		angularV = 0.0f;
		acceleration = bhVec2(0.0f, 0.0f);
		force = bhVec2(0.0f, 0.0f);
		mass = 0.0f;
		bodyGravity = 0.0f;
		angle = 0.0f;
	}

	~bhBody() {};

	inline void AddForce(bhVec2 f)
	{
		force += f;
	}
	

	// ===================================================
	//					Setters
	// ===================================================

	// Set body position 
	inline void SetPosition(bhVec2 pos)
	{
		position = pos;
	}
	inline void SetPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	// Set body linear speed
	inline void SetLinearVelocity(bhVec2 v)
	{
		linearV = v;
	}
	inline void SetLinearVelocity(float x, float y)
	{
		linearV.x = x;
		linearV.y = y;
	}

	// Set body angluar speed
	inline void SetAngularVelocity(float v)
	{
		angularV = v;
	}
	
	// ===================================================
	//					Getters
	// ===================================================

	// Get the body position
	inline bhVec2 GetPosition()const
	{
		return position;
	}
	
	// Get the body linear velocity
	inline bhVec2 GetLinearVelocity() const
	{
		return linearV;
	}

	// Get the body angular velocity
	inline float GetAngularVelocity() const
	{
		return angularV;
	}

	// Get the body acceleration
	inline bhVec2 GetAcceleration() const
	{
		return acceleration;
	}

	// Get body mass
	inline float GetBodyMass() const
	{
		return mass;
	}

	//Get gravity on the body;
	inline float GetBodyGravity() const
	{
		return bodyGravity;
	}

	// Get the body angle
	inline float GetBodyAngle() const
	{
		return angle;
	}
};