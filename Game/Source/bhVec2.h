#pragma once

#include <math.h>

class bhVec2
{
public:
	double x = 0;
	double y = 0;

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

	// Negate a vector
	bhVec2 Negate()
	{
		bhVec2 aux;
		aux.x = -x;
		aux.y = -y;
		
		return aux;
	}

	// Get the perpendicular vector
	bhVec2 Perpendicular(bhVec2& v)
	{
		bhVec2 ret;
		ret.x = v.y;
		ret.y = -v.x;
		return ret;
	}

	bhVec2 Normalize()
	{
		bhVec2 aux = bhVec2(x, y);
		float l = sqrt(pow(aux.x, 2) + pow(aux.y, 2));
		aux = aux / l;
		return aux;
	}

	float Dot(bhVec2& v)
	{
		return x * v.x + y * v.y;
	}

	// Vector addition
	void operator += (const bhVec2& v)
	{
		x += v.x;
		y += v.y;
	}
	
	bhVec2 operator + (const bhVec2& v)
	{
		bhVec2 nv;
		nv.x = x + v.x;
		nv.y = y + v.y;
		return nv;
	}

	bhVec2 operator + (const float& a)
	{
		bhVec2 nv;
		nv.x = x + a;
		nv.y = y + a;
		return nv;
	}

	// Vector substraction
	void operator -= (const bhVec2& v)
	{
		x -= v.x;
		y -= v.y;
	}

	bhVec2 operator- (bhVec2& v)
	{
		bhVec2 nv;
		nv.x = x - v.x;
		nv.y = y - v.y;
		return nv;
	}

	// Multply a vector by a scalar
	bhVec2 operator *= (float a)
	{
		bhVec2 nv;
		nv.x = x * a;
		nv.y = y * a;
		return nv;
	}

	bhVec2 operator*(bhVec2& a)
	{
		bhVec2 nv;
		nv.x = x * a.x;
		nv.y = y * a.y;
		return nv;
	}

	bhVec2 operator*(float a)
	{
		bhVec2 aux;
		aux.x = x * a;
		aux.y = y * a;

		return aux;
	}

	void operator*(double& a)
	{
		x = x * a;
		y = y * a;
	}

	bhVec2 operator/(float& a)
	{
		bhVec2 nv;
		nv.x = x / a;
		nv.y = y / a;
		return nv;
	}
	
	bool operator< (bhVec2 v)
	{
		return (x < v.x) && (y < v.y);
	}
};