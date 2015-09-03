/**
 * @class Mat4x4
 *
 * @brief Basic Matrix 4x4 Math class
 *
 * This class is for Matrix4.
 * It holds a union of structures (16 floats / array of 16 floats / 4 arrays of 4 floats).
 * Holds all relative functions and operator overloads
 *
 * @author Shane Coates
 *
 * @date 12/06/2014
 */

#ifndef MAT4X4_H
#define	MAT4X4_H

#include <ostream>


class Vec2;
class Vec3;

class Mat4x4
{
public:

	union
	{
		struct
		{
			float 	m1,  m2,  m3,  m4,
					m5,  m6,  m7,  m8,
					m9,  m10, m11, m12,
					m13, m14, m15, m16;
		};

		struct
		{
			float m[16];
		};
	
		struct
		{
			float mm[4][4];
		};
	
	};

	/// @brief	Default Constructor
	Mat4x4();

	/// @brief	Creates a blank (Identity) Matrix
	void CreateIdentity();

	/// @brief	Copies an existing matrix into the current one
	///	@param	const Mat4x4& src
	void CopyFrom(const Mat4x4& src);

	///	@brief	Creates a matrix for use as an Orthographic
	///	@param	float left, @param float right, @param float bottom, @param float top, @param float near, @param float far
	///	@return	Mat4x4
	static Mat4x4 CreateOrthographic(float left, float right, float bottom, float top, float near, float far);

	/// @brief	Prints the current Matrix4 to console
	friend std::ostream& operator << (std::ostream& stream, const Mat4x4& mat)
	{
		stream	<< mat.m1  << " " << mat.m2  << " "  << mat.m3  << mat.m4 << std::endl	
				<< mat.m5  << " " << mat.m6  << " "  << mat.m7  << mat.m8 << std::endl
				<< mat.m9  << " " << mat.m10 << " "  << mat.m11 << mat.m12 << std::endl
				<< mat.m13 << " " << mat.m14 << " "  << mat.m15 << mat.m16 << std::endl;

		return stream;
	}

private:

};


#endif