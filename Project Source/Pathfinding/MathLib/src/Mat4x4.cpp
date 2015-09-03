#include "Mat4x4.h"

Mat4x4::Mat4x4()
{
	CreateIdentity();
}

void Mat4x4::CreateIdentity()
{
	for(int i = 0; i < 16; i ++)
		m[i] = 0;

	mm[0][0] = 1;
	mm[1][1] = 1;
	mm[2][2] = 1;
	mm[3][3] = 1;
}

void Mat4x4::CopyFrom(const Mat4x4& src)
{
	for(int i = 0; i < 16; i++)
	{
		m[i] = src.m[i];
	}
}

Mat4x4 Mat4x4::CreateOrthographic(float left, float right, float bottom, float top, float near, float far)
{
	Mat4x4 res;

	float w = right - left;
	float h = top - bottom;
	float d = far - near;

	res.m[0]	=  2.0f / w;
	res.m[1]	=  0.0f;
	res.m[2]	=  0.0f;
	res.m[3]	=  0.0f;
	res.m[4]	=  0.0f;
	res.m[5]	=  2.0f / h;
	res.m[6]	=  0.0f;
	res.m[7]	=  0.0f;
	res.m[8]	=  0.0f;
	res.m[9]	=  0.0f;
	res.m[10]	=  2.0f / d;
	res.m[11]	=  0.0f;
	res.m[12]	= -1.0f * ( (right + left) / w );
	res.m[13]	= -1.0f * ( (top + bottom) / h );
	res.m[14]	= -1.0f * ( (far + near)   / d );
	res.m[15]	=  1.0f;

	return res;
}