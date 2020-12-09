#pragma once

class bhVec2
{
public:
	float x = 0;
	float y = 0;

public:
	bhVec2() {};

	bhVec2(float newX, float newY)
	{
		x = newX;
		y = newY;
	}

	// Set new values for the vector
	void SetVector(float newX, float newY)
	{
		x = newX;
		y = newY;
	}

	// Ngeate a vector
	bhVec2 Negate(bhVec2 v)
	{
		v.x = -v.x; 
		v.y = -v.y;
	}

	// Vector addition
	void operator += (const bhVec2 v)
	{
		x += v.x;
		y += v.y;
	}

	// Vector substraction
	void operator -= (const bhVec2 v)
	{
		x -= v.x;
		y -= v.y;
	}

	// Multply a vector by a scalar
	void operator *= (float a)
	{
		x *= a;
		y *= a;
	}

	void operator*(bhVec2 a)
	{
		x = x * a.x;
		y = y * a.y;
	}

	void operator*(float a)
	{
		x *= a;
		y *= a;
	}
};