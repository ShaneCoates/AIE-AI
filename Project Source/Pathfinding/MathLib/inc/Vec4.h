/**
 * @class Vec4
 *
 * @brief Basic Vector4 Math class
 *
 * This class is for Vector4.
 * It holds a union of structures (4 floats / array of 4 floats), both with position or colour variable names.
 * Holds all relative functions and operator overloads
 *
 * @author Shane Coates
 *
 * @date 12/06/2014
 */

#ifndef VEC4_H
#define	VEC4_H

#include "math.h"

class Vec4
{
public:
	union 
	{
		struct
		{
			float rgba[4];
		};
		struct
		{
			float r, g, b, a;
		};
		float xyzw[4];
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			float top, bottom, left, right;
		};

	};

	/// @brief Overload Constructor
	Vec4(float a_x = 0.0f, float a_y = 0.0f, float a_z = 0.0f, float a_w = 0.0f) 
		: r(a_x), g(a_y), b(a_z), a(a_w) {}

	/// @brief Sets colour values
	/// @param float a_r,@param float a_g,@param float a_b,@param float a_a
	void SetColour(float a_r, float a_g, float a_b, float a_a)
	{
		r = a_r;
		g = a_g;
		b = a_b;
		a = a_a;
	}

	Vec4 operator+(const Vec4& rhs) const
	{
		return Vec4(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w);
	}

	Vec4 operator-(const Vec4& rhs) const
	{
		return Vec4(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w);
	}

protected:
private:


};

#endif