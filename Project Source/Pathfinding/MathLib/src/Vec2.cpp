#include "Vec2.h"
#include "Vec3.h"
#include "Mat3x3.h"
#include <math.h>

float Vec2::Length()
{
	return sqrt(x*x + y*y);
}

Vec2& Vec2::Normalise()
{
	float len = Length();
	x /= len;
	y /= len;

	return *this;
}

float Vec2::Dot(Vec2 &rhs)
{
	return (x * rhs.x) + (y * rhs.y);
}

float Vec2::GetAngle(Vec2 A, Vec2 B)
{
	return acosf(A.Dot(B) / (A.Length() * B.Length()));
	//A.Normalise();
	//B.Normalise();

	//Vec2 AP = Vec2(A.y, -A.x);
	//float rot = acos(A.Dot(B));
	//if(AP.Dot(B) < 0)
	//	rot = -rot;
	//return rot;
}

Vec2 Vec2::GetPerpClockwise(Vec2 A)
{
	return Vec2(A.y, -A.x);
}

Vec2 Vec2::GetPerpCounterClockwise(Vec2 A)
{
	return Vec2(-A.y, A.x);
}


//Vector2 overloads:

Vec2 Vec2::operator+ (const Vec2 &rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator- (const Vec2 &rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2& Vec2::operator+= (const Vec2 &rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vec2& Vec2::operator-= (const Vec2 &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vec2 Vec2::operator* (const Vec2 &rhs) const
{
	return Vec2(x * rhs.x, y * rhs.y);
}

Vec2 Vec2::operator/ (const Vec2 &rhs) const
{
	return Vec2(x / rhs.x, y / rhs.y);
}

Vec2& Vec2::operator*= (const Vec2 &rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

Vec2& Vec2::operator/= (const Vec2 &rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}

//Scalar overloads:
Vec2 Vec2::operator	/ (const float &rhs) const
{
	return Vec2(x / rhs, y / rhs);
}

Vec2 Vec2::operator	* (const float &rhs) const
{
	return Vec2(x * rhs, y * rhs);
}

Vec2& Vec2::operator/= (const float &rhs)
{
	x /= rhs;
	y /= rhs;
	return *this;
}

Vec2& Vec2::operator*= (const float &rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

//Matrix overloads
Vec2 Vec2::operator * (const Mat3x3& rhs) const
{
	
	return Vec2(Vec3::DotProduct(Vec3((*this).x, (*this).y, 1.0f), Vec3(rhs.m1, rhs.m4, rhs.m7)),
				Vec3::DotProduct(Vec3((*this).x, (*this).y, 1.0f), Vec3(rhs.m2, rhs.m5, rhs.m8)));

}