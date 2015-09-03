#include "Vec3.h"
#include "Mat3x3.h"
#include <math.h>

float Vec3::Length()
{
	return sqrt(x*x + y*y + z*z);
}

void Vec3::Normalise()
{
	float len = Length();
	x /= len;
	y /= len;
	z /= len;
}

float Vec3::Dot(Vec3 &rhs)
{
	return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}

Vec3 Vec3::Cross(Vec3 &rhs)
{
	return Vec3(y * rhs.z - z * rhs.y,
				z * rhs.x - x * rhs.z, 
				x * rhs.y - y * rhs.x);
}

float Vec3::DotProduct(Vec3 A, Vec3 B)
{
	return (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
}

Vec3 Vec3::CrossProduct(Vec3 A, Vec3 B)
{
	return Vec3(A.y * B.z - A.z * B.y, 
				A.z * B.x - A.x * B.z, 
				A.x * B.y - A.y * B.x);
}

float Vec3::GetAngle(Vec3 A, Vec3 B)
{
	return acosf(A.Dot(B) / (A.Length() * B.Length()));
}


//Vector3 overloads:

Vec3 Vec3::operator+ (const Vec3 &rhs) const
{
	return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vec3 Vec3::operator- (const Vec3 &rhs) const
{
	return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vec3& Vec3::operator+= (const Vec3 &rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vec3& Vec3::operator-= (const Vec3 &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vec3 Vec3::operator* (const Vec3 &rhs) const
{
	return Vec3(x * rhs.x, y * rhs.y, z * rhs.z);
}

Vec3 Vec3::operator/ (const Vec3 &rhs) const
{
	return Vec3(x / rhs.x, y / rhs.y, z / rhs.z);
}

Vec3& Vec3::operator*= (const Vec3 &rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

Vec3& Vec3::operator/= (const Vec3 &rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}

//Scalar overloads:
Vec3 Vec3::operator	/ (float rhs) const
{
	return Vec3(x / rhs, y / rhs, z / rhs);
}

Vec3 Vec3::operator	* (float rhs) const
{
	return Vec3(x * rhs, y * rhs, z * rhs);
}

Vec3& Vec3::operator/= (float rhs)
{
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}

Vec3& Vec3::operator*= (float rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

//Matrix overloads
Vec3 Vec3::operator * (const Mat3x3& rhs) const
{
	
	return Vec3(DotProduct(*this, Vec3(rhs.m1, rhs.m4, rhs.m7)),
				DotProduct(*this, Vec3(rhs.m2, rhs.m5, rhs.m8)),
				DotProduct(*this, Vec3(rhs.m3, rhs.m6, rhs.m9)));

}