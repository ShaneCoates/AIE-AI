/**
 * @class Mat3x3
 *
 * @brief Basic Matrix 3x3 Math class
 *
 * This class is for Matrix3.
 * It holds a union of structures (9 floats / array of 9 floats / 3 arrays of 3 floats).
 * Holds all relative functions and operator overloads
 *
 * @author Shane Coates
 *
 * @date 12/06/2014
 */

#ifndef MAT3X3_H
#define	MAT3X3_H

#include <ostream>


class Vec2;
class Vec3;

class Mat3x3
{
public:

	union
	{
		struct
		{
			float 	m1, m2, m3,
					m4, m5, m6,
					m7, m8, m9;
		};

		struct
		{
			float m[9];
		};
	
		struct
		{
			float mm[3][3];
		};
	
	};

	/// @brief Default Constructor
	Mat3x3();

	/// @brief	Overloaded Constructor of ugliness
	///	@param	floats a_m1, a_m2, a_m3, @param floats a_m4, a_m5, a_m6, @param floats a_m7, a_m8, a_m9
	Mat3x3(	float a_m1, float a_m2, float a_m3,
			float a_m4, float a_m5, float a_m6,
			float a_m7, float a_m8, float a_m9);

	/// @brief	Creates a blank(Identity) matrix
	void CreateIdentity();

	/// @brief	Copies the contests of a matrix into this
	///	@param	const Mat3x3& src
	void CopyFrom(const Mat3x3& src);

	/// @brief	Creates a blank Rotation matrix
	///	@param	float angle
	///	@return	Mat3x3
	static Mat3x3 CreateRotation(float angle);

	/// @brief	Creates a blank Translation matrix
	///	@param	const Vec2& translation
	///	@return	Mat3x3
	static Mat3x3 CreateTranslation(const Vec2& translation);

	/// @brief	Returns the current translation
	///	@return	Vec2
	Vec2 GetTranslation();

	/// @brief	Returns the rotation from the y axis
	///	@return	float
	float GetUpRotation();

	/// @brief	Returns the rotation from the x axis
	///	@return	float
	float GetRightRotation();

	/// @brief	Translates the current Matrix3
	///	@param	const Vec2& trans
	void Translate(const Vec2& trans);

	/// @brief	Translates the current Matrix3 on a global scale
	///	@param	const Vec2& trans
	void TranslateGlobal(const Vec2& trans);

	/// @brief	Rotate the current Matrix3
	///	@param	float angle
	void Rotate(float angle);

	/// @brief	Sets the Translation of the current Matrix3
	///	@param	float angle
	void SetTranslation(const Vec2& trans);

	/// @brief	Sets the Rotation of the current Matrix3
	///	@param	float rot
	void SetRotation(float rot);

	/// @brief	Returns the scale of the x axis
	///	@return	float
	float GetXScale();

	/// @brief	Returns the scale of the y axis
	///	@return	float
	float GetYScale();

	/// @brief	Returns the scale of both axis'
	///	@return	Vec2
	Vec2 GetScale();

	/// @brief	Sets the scale on both axis'
	///	@param	Vec2 scale
	void SetScale(Vec2 scale);

	/// @brief	Sets the scale on both axis'
	///	@param	float X, @param float Y
	void SetScale(float X, float Y);

	/// @brief	Transforms a specified point
	///	@param	const Vec3& point
	///	@return Vec3
	Vec3 TransformPoint(const Vec3& point) const;					

	Mat3x3& operator	*	(const Mat3x3	&rhs) const;			///< '*'	operator overload with Matrix3 and Matrix3
	Mat3x3& operator	*=	(const Mat3x3	&rhs);					///< '*='	operator overload with Matrix3 and Matrix3

	Mat3x3 operator		*	(float scalar) const;					///< '+'	operator overload with Matrix3 and float
	Mat3x3 operator		*=	(float scalar);							///< '+'	operator overload with Matrix3 and float
	
	Vec3& operator		*	(const Vec3		&rhs) const;			///< '+'	operator overload with Matrix3 and Vec3

	/// @brief	Prints the current Matrix to the screen
	friend std::ostream& operator << (std::ostream& stream, const Mat3x3& mat)
	{
		stream	<< mat.m1 << " " << mat.m2 << " " << mat.m3 << std::endl	
				<< mat.m4 << " " << mat.m5 << " " << mat.m6 << std::endl
				<< mat.m7 << " " << mat.m8 << " " << mat.m9;

		return stream;
	}

private:


};
#endif