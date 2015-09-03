#include "Mat3x3.h"
#include "Vec2.h"
#include "Vec3.h"

Mat3x3::Mat3x3()
{
	CreateIdentity();
}

Mat3x3::Mat3x3(float a_m1, float a_m2, float a_m3,
			   float a_m4, float a_m5, float a_m6,
			   float a_m7, float a_m8, float a_m9) :
					m1(a_m1), m2(a_m2), m3(a_m3),
					m4(a_m4), m5(a_m5), m6(a_m6),
					m7(a_m7), m8(a_m8), m9(a_m9)
{

}

void Mat3x3::CreateIdentity()
{
	for(int i = 0; i < 9; i ++)
		m[i] = 0;

	mm[0][0] = 1;
	mm[1][1] = 1;
	mm[2][2] = 1;
}

void Mat3x3::CopyFrom(const Mat3x3& src)
{
	for(int i = 0; i < 9; i++)
	{
		m[i] = src.m[i];
	}
}

Mat3x3 Mat3x3::CreateRotation(float angle)
{
	Mat3x3 mat;
	mat.SetRotation(angle);
	return mat;
}

Mat3x3 Mat3x3::CreateTranslation(const Vec2& translation)
{
	Mat3x3 mat;
	mat.SetTranslation(translation);
	return mat;
}

Vec2 Mat3x3::GetTranslation()
{
	return Vec2(m7, m8);
}

float Mat3x3::GetUpRotation()
{
	Vec2 up(0, 1);
	Vec2 localUp(m4, m5);
	localUp.Normalise();

	if(localUp.x < 0)
		return -Vec2::GetAngle(up, localUp);
	return Vec2::GetAngle(up, localUp);
}

float Mat3x3::GetRightRotation()
{
	Vec2 right(1, 0);
	Vec2 localRight(m1, m2);
	localRight.Normalise();

	return Vec2::GetAngle(right, localRight);
}

void Mat3x3::Translate(const Vec2& trans)
{
	*this = CreateTranslation(trans) * *this;
}

void Mat3x3::TranslateGlobal(const Vec2& trans)
{
	m7 += trans.x;
	m8 += trans.y;
}

void Mat3x3::Rotate(float angle)
{
	*this = CreateRotation(angle) * *this;
}

void Mat3x3::SetTranslation(const Vec2& trans)
{
	m7 = trans.x;
	m8 = trans.y;
}

void Mat3x3::SetRotation(float rot)
{
	m1 = cosf(rot);
	m2 = -sinf(rot);
	m4 = sinf(rot);
	m5 = cosf(rot);
}

float Mat3x3::GetXScale()
{
	return Vec2(m1, m2).Length();
}

float Mat3x3::GetYScale()
{
	return Vec2(m4, m5).Length();
}

Vec2 Mat3x3::GetScale()
{
	return Vec2(Vec2(m1, m2).Length(), 
				Vec2(m4, m5).Length());
}

void Mat3x3::SetScale(Vec2 scale)
{
	Vec2 xAxis(m1, m2);
	Vec2 yAxis(m4, m5);
	
	xAxis.Normalise() *= scale.x;
	yAxis.Normalise() *= scale.y;
	
	m1 = xAxis.x;
	m2 = xAxis.y;
	m4 = yAxis.x;
	m5 = yAxis.y;
}

void Mat3x3::SetScale(float X, float Y)
{
	Vec2 xAxis(m1, m2);
	Vec2 yAxis(m4, m5);
	
	xAxis.Normalise() *= X;
	yAxis.Normalise() *= Y;
	
	m1 = xAxis.x;
	m2 = xAxis.y;
	m4 = yAxis.x;
	m5 = yAxis.y;
}

Vec3 Mat3x3::TransformPoint(const Vec3& point) const
{
	Vec3 res;

	res.x = Vec3::DotProduct(Vec3(m1, m2, m3), Vec3(point.x, point.y, point.z));
	res.y = Vec3::DotProduct(Vec3(m4, m5, m6), Vec3(point.x, point.y, point.z));
	res.z = Vec3::DotProduct(Vec3(m7, m8, m9), Vec3(point.x, point.y, point.z));

	return res;
}

Mat3x3& Mat3x3::operator * (const Mat3x3 &rhs) const
{
	Mat3x3 mat;

	//row 1
	mat.m1 = Vec3::DotProduct(Vec3(m1, m2, m3), Vec3(rhs.m1, rhs.m4, rhs.m7));
	mat.m2 = Vec3::DotProduct(Vec3(m1, m2, m3), Vec3(rhs.m2, rhs.m5, rhs.m8));
	mat.m3 = Vec3::DotProduct(Vec3(m1, m2, m3), Vec3(rhs.m3, rhs.m6, rhs.m9));
			 
	//row 2	 
	mat.m4 = Vec3::DotProduct(Vec3(m4, m5, m6), Vec3(rhs.m1, rhs.m4, rhs.m7));
	mat.m5 = Vec3::DotProduct(Vec3(m4, m5, m6), Vec3(rhs.m2, rhs.m5, rhs.m8));
	mat.m6 = Vec3::DotProduct(Vec3(m4, m5, m6), Vec3(rhs.m3, rhs.m6, rhs.m9));
			 
	//row 3	 
	mat.m7 = Vec3::DotProduct(Vec3(m7, m8, m9), Vec3(rhs.m1, rhs.m4, rhs.m7));
	mat.m8 = Vec3::DotProduct(Vec3(m7, m8, m9), Vec3(rhs.m2, rhs.m5, rhs.m8));
	mat.m9 = Vec3::DotProduct(Vec3(m7, m8, m9), Vec3(rhs.m3, rhs.m6, rhs.m9));

	return mat;
}

Mat3x3& Mat3x3::operator *= (const Mat3x3 &rhs)
{

	return *this = *this * rhs;

	//Mat3x3 mat = lhs * *this;
	//for(int di = 0; di < 3; di++)
	//{
	//	for(int dj = 0; dj < 3; dj++)
	//	{
	//		mm[di][dj] = mat.mm[di][dj];
	//	}
	//}
	//return *this;
}

Vec3& Mat3x3::operator * (const Vec3	&rhs) const
{
	return Vec3(0, 0, 0);
}

Mat3x3 Mat3x3::operator * (float scalar) const
{
	Mat3x3 mat;

	for(int i = 0; i < 9; i++)
	{
		mat.m[i] = m[i] * scalar;
	}
	return mat;
}

Mat3x3 Mat3x3::operator *= (float scalar)
{
	for(int i = 0; i < 9; i++)
	{
		m[i] *= scalar;
	}

	return *this;
}