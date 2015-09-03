
#include <math.h>

namespace Curve
{

enum CURVE_TYPE
{
	LINEARINTERPOLATION,

	QUADRATICEASEOUT,
	QUADRATICEASEIN,
	QUADRATICEASEINOUT,

	CUBICEASEOUT,
	CUBICEASEIN,
	CUBICEASEINOUT,

	QUARTICEASEOUT,
	QUARTICEASEIN,
	QUARTICEASEINOUT,

	QUINTICEASEOUT,
	QUINTICEASEIN,
	QUINTICEASEINOUT,

	SINUSOIDALEASEOUT,
	SINUSOIDALEASEIN,
	SINUSOIDALEASEINOUT,

	EXPONENTIALEASEOUT,
	EXPONENTIALEASEIN,
	EXPONENTIALEASEINOUT,

	CIRCULAREASEOUT,
	CIRCULAREASEIN,
	CIRCULAREASEINOUT,


	CURVE_TYPE_COUNT
};

// Get the name of the curve as a literal string
const char *GetCurveName(CURVE_TYPE type);

// call this function with the curve type using the enum above.
float CurveFunc(CURVE_TYPE type, float t, float start, float end);


// The following curve functions were copied from the following website:
// http://iphonedevelopment.blogspot.com.au/2010/12/more-animation-curves-than-you-can.html
// and slightly modified, as many had errors with lerps between small numbers. EG: 0 - PI
// the curves below are released under public domain from the above website,
// though acknologing where they come from is often nice.
//------------------------------------------------------------

	float LinearInterpolation	(float t, float start, float end);

	float QuadraticEaseOut		(float t, float start, float end);
	float QuadraticEaseIn		(float t, float start, float end);
	float QuadraticEaseInOut	(float t, float start, float end);

	float CubicEaseOut			(float t, float start, float end);
	float CubicEaseIn			(float t, float start, float end);
	float CubicEaseInOut		(float t, float start, float end);

	float QuarticEaseOut		(float t, float start, float end);
	float QuarticEaseIn			(float t, float start, float end);
	float QuarticEaseInOut		(float t, float start, float end);

	float QuinticEaseOut		(float t, float start, float end);
	float QuinticEaseIn			(float t, float start, float end);
	float QuinticEaseInOut		(float t, float start, float end);

	float SinusoidalEaseOut		(float t, float start, float end);
	float SinusoidalEaseIn		(float t, float start, float end);
	float SinusoidalEaseInOut	(float t, float start, float end);

	float ExponentialEaseOut	(float t, float start, float end);
	float ExponentialEaseIn		(float t, float start, float end);
	float ExponentialEaseInOut	(float t, float start, float end);

	float CircularEaseOut		(float t, float start, float end);
	float CircularEaseIn		(float t, float start, float end);
	float CircularEaseInOut		(float t, float start, float end);

//------------------------------------------------------------

}