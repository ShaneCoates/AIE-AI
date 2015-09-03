/**
 * @class Vec2
 *
 * @brief Basic Vector2 Math class
 *
 * This class is for Vector2.
 * It holds a union of structures (2 floats / array of 2 floats).
 * Holds all relative functions and operator overloads
 *
 * @author Shane Coates
 *
 * @date 12/06/2014
 */

#ifndef VEC2_H
#define	VEC2_H

#include "math.h"
#include "Mat3x3.h"

class Vec2
{
public:

	union 
	{
		struct
		{
			float xy[2];
		};
		struct
		{
			float x, y;
		};
	};

	/// @brief Overload Constructor
	Vec2(float X = 0, float Y = 0) : x(X), y(Y) {}

	///	@brief	Returns the length of the vector
	///	@return	float
	float Length();

	///	@brief	Normalises the given vector to length 1
	///	@return	Vec2
	Vec2 &Normalise();

	///	@brief	Returns the Dot Product of this vector and another
	///	@param	Vec2 &rhs
	///	@return	float
	float Dot(Vec2 &rhs);

	///	@brief	Returns the angle between two vectors
	///	@param	Vec2 A, @param Vec2 B
	///	@return	float
	static float GetAngle(Vec2 A, Vec2 B);

	///	@brief	Returns a vector that is perpendicular to the current, clockwise
	///	@param	Vec2 A
	///	@return	Vec2
	Vec2 GetPerpClockwise(Vec2 A);

	///	@brief	Returns a vector that is perpendicular to the current, counter-clockwise
	///	@param	Vec2 A
	///	@return	Vec2
	Vec2 GetPerpCounterClockwise(Vec2 A);

	Vec2 operator	+	(const Vec2 &rhs) const;	///< '+'	operator overload with Vec2 and Vec2
	Vec2 operator	-	(const Vec2 &rhs) const;	///< '-'	operator overload with Vec2 and Vec2
	Vec2& operator	+=	(const Vec2 &rhs);			///< '+='	operator overload with Vec2 and Vec2
	Vec2& operator	-=	(const Vec2 &rhs);			///< '-='	operator overload with Vec2 and Vec2
	Vec2 operator	*	(const Vec2 &rhs) const;	///< '*'	operator overload with Vec2 and Vec2
	Vec2 operator	/	(const Vec2 &rhs) const;	///< '/'	operator overload with Vec2 and Vec2
	Vec2& operator	*=	(const Vec2 &rhs);			///< '*='	operator overload with Vec2 and Vec2
	Vec2& operator	/=	(const Vec2 &rhs);			///< '/='	operator overload with Vec2 and Vec2
													   
													   
	Vec2 operator	/	(const float &rhs) const;	///< '/'	operator overload with Vec2 and scalar
	Vec2 operator	*	(const float &rhs) const;	///< '*'	operator overload with Vec2 and scalar
	Vec2& operator	/=	(const float &rhs);			///< '/='	operator overload with Vec2 and scalar
	Vec2& operator	*=	(const float &rhs);			///< '*='	operator overload with Vec2 and scalar
													   
	Vec2 operator	*   (const Mat3x3& rhs) const;	///< '*='	operator overload with Vec2 and Matrix 3
protected:
private:


};

#endif