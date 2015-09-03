/**
 * @class Vec3
 *
 * @brief Basic Vector3 Math class
 *
 * This class is for Vector3.
 * It holds a union of structures (3 floats / array of 3 floats).
 * Holds all relative functions and operator overloads
 *
 * @author Shane Coates
 *
 * @date 12/06/2014
 */

#ifndef VEC3_H
#define	VEC3_H

#include "math.h"

class Mat3x3;
class Vec3
{
public:

	/// @brief Union holding 3 float values
	union 
	{
		struct
		{
			float xyz[3];	
		};
		struct
		{
			float x, y, z;	
		};
	};

	/// @brief Overload Constructor
	Vec3(float X = 0, float Y = 0, float Z = 0) : x(X), y(Y), z(Z) {}

	///	@brief	Returns the length of the current Vector
	///	@return	float
	float Length();

	/// @brief	Normalises the Vector to Length of 1
	void Normalise(); 

	///	@brief	Returns the Dot Product of two vectors
	///	@param	Vec3 &rhs
	///	@return	float
	float Dot(Vec3 &rhs);

	///	@brief	Returns the Cross Product of two vectors
	///	@param	Vec3 &rhs
	///	@return	Vec3
	Vec3 Cross(Vec3 &rhs);

	///	@brief	Returns the angle between two vectors
	///	@param	Vec3 A, @param Vec3 B
	///	@return	float
	static float GetAngle(Vec3 A, Vec3 B);
	
	///	@brief	Returns the Dot Product between two vectors
	///	@param	Vec3 A, @param Vec3 B
	///	@return	float
	static float DotProduct(Vec3 A, Vec3 B);

	/// @brief	Returns the Cross Product between two vectors
	/// @param	Vec3 A, @param Vec3 B
	/// @return	Vec3
	static Vec3 CrossProduct(Vec3 A, Vec3 B); 

	
	Vec3 operator	+	(const Vec3 &rhs) const; 	///< '+'	operator overload with Vec3 and Vec3
	Vec3 operator	-	(const Vec3 &rhs) const; 	///< '-'	operator overload with Vec3 and Vec3
	Vec3& operator	+=	(const Vec3 &rhs);		 	///< '+='	operator overload with Vec3 and Vec3
	Vec3& operator	-=	(const Vec3 &rhs);		 	///< '-='	operator overload with Vec3 and Vec3
	Vec3 operator	*	(const Vec3 &rhs) const; 	///< '*'	operator overload with Vec3 and Vec3
	Vec3 operator	/	(const Vec3 &rhs) const; 	///< '/'	operator overload with Vec3 and Vec3
	Vec3& operator	*=	(const Vec3 &rhs);		 	///< '*='	operator overload with Vec3 and Vec3
	Vec3& operator	/=	(const Vec3 &rhs);		 	///< '/='	operator overload with Vec3 and Vec3
													   
													   
	Vec3 operator	/	(float rhs) const;			///< '/'	operator overload with Vec3 and scalar
	Vec3 operator	*	(float rhs) const;			///< '*'	operator overload with Vec3 and scalar
	Vec3& operator	/=	(float rhs);				///< '/='	operator overload with Vec3 and scalar
	Vec3& operator	*=	(float rhs);				///< '*='	operator overload with Vec3 and scalar
													   
													
	Vec3 operator * (const Mat3x3& rhs) const;		///< '*'	operator overload with Vec3 and Matrix 3
	Vec3 operator *= (const Mat3x3& rhs);			///< '*='	operator overload with Vec3 and Matrix 3

protected:
private:


};

#endif