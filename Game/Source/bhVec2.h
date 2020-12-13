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

	// Negate a vector
	bhVec2 Negate()
	{
		bhVec2 aux;
		aux.x = -x;
		aux.y = -y;
		
		return aux;
	}

	// Get the perpendicular vector
	//bhVec2 Perpendicular(bhVec2& v)
	//{
	//	x = -v.y;
	//	y = v.x;
	//	bhVec2 ret = bhVec2(x, y);
	//	return ret;
	//}

	// Vector addition
	void operator += (const bhVec2& v)
	{
		x += v.x;
		y += v.y;
	}
	
	bhVec2 operator + (const bhVec2& v)
	{
		bhVec2 nv;
		nv.x += v.x;
		nv.y += v.y;
		return nv;
	}

	// Vector substraction
	void operator -= (const bhVec2& v)
	{
		x -= v.x;
		y -= v.y;
	}

	// Multply a vector by a scalar
	void operator *= (float& a)
	{
		x *= a;
		y *= a;
	}

	void operator*(bhVec2& a)
	{
		x = x * a.x;
		y = y * a.y;
	}

	bhVec2 operator*(float& a)
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
		nv.x /= a;
		nv.y /= a;
		return nv;
	}
	
	bool operator< (bhVec2 v)
	{
		return x < v.x && y < v.y;
	}
};