
#include "Curve.h"

#define _USE_MATH_DEFINES
#include <math.h>


#define BoundsCheck(t, start, end) \
if (t <= 0.f) return start;        \
else if (t >= 1.f) return end;


float Curve::CurveFunc(CURVE_TYPE type, float t, float start, float end)
{
	switch( type )
	{
		case LINEARINTERPOLATION:	return Curve::LinearInterpolation	( t,  start,  end);	

		case QUADRATICEASEOUT:		return Curve::QuadraticEaseOut		( t,  start,  end);	
		case QUADRATICEASEIN:		return Curve::QuadraticEaseIn		( t,  start,  end);	
		case QUADRATICEASEINOUT:	return Curve::QuadraticEaseInOut	( t,  start,  end);	

		case CUBICEASEOUT:			return Curve::CubicEaseOut			( t,  start,  end);	
		case CUBICEASEIN:			return Curve::CubicEaseIn			( t,  start,  end);	
		case CUBICEASEINOUT:		return Curve::CubicEaseInOut		( t,  start,  end);	

		case QUARTICEASEOUT:		return Curve::QuarticEaseOut		( t,  start,  end);	
		case QUARTICEASEIN:			return Curve::QuarticEaseIn			( t,  start,  end);	
		case QUARTICEASEINOUT:		return Curve::QuarticEaseInOut		( t,  start,  end);	

		case QUINTICEASEOUT:		return Curve::QuinticEaseOut		( t,  start,  end);	
		case QUINTICEASEIN:			return Curve::QuinticEaseIn			( t,  start,  end);	
		case QUINTICEASEINOUT:		return Curve::QuinticEaseInOut		( t,  start,  end);	

		case SINUSOIDALEASEOUT:		return Curve::SinusoidalEaseOut		( t,  start,  end);	
		case SINUSOIDALEASEIN:		return Curve::SinusoidalEaseIn		( t,  start,  end);	
		case SINUSOIDALEASEINOUT:	return Curve::SinusoidalEaseInOut	( t,  start,  end);	

		case EXPONENTIALEASEOUT:	return Curve::ExponentialEaseOut	( t,  start,  end);	
		case EXPONENTIALEASEIN:		return Curve::ExponentialEaseIn		( t,  start,  end);	
		case EXPONENTIALEASEINOUT:	return Curve::ExponentialEaseInOut	( t,  start,  end);	

		case CIRCULAREASEOUT:		return Curve::CircularEaseOut		( t,  start,  end);	
		case CIRCULAREASEIN:		return Curve::CircularEaseIn		( t,  start,  end);	
		case CIRCULAREASEINOUT:		return Curve::CircularEaseInOut		( t,  start,  end);	

		default: 
		return Curve::LinearInterpolation	( t,  start,  end);
	}
}

const char *Curve::GetCurveName(Curve::CURVE_TYPE type)
{
	switch( type )
	{
		case LINEARINTERPOLATION:	return "LinearInterpolation";

		case QUADRATICEASEOUT:		return "QuadraticEaseOut";
		case QUADRATICEASEIN:		return "QuadraticEaseIn";
		case QUADRATICEASEINOUT:	return "QuadraticEaseInOut";

		case CUBICEASEOUT:			return "CubicEaseOut";
		case CUBICEASEIN:			return "CubicEaseIn";
		case CUBICEASEINOUT:		return "CubicEaseInOut";

		case QUARTICEASEOUT:		return "QuarticEaseOut";
		case QUARTICEASEIN:			return "QuarticEaseIn";
		case QUARTICEASEINOUT:		return "QuarticEaseInOut";

		case QUINTICEASEOUT:		return "QuinticEaseOut";
		case QUINTICEASEIN:			return "QuinticEaseIn";
		case QUINTICEASEINOUT:		return "QuinticEaseInOut";

		case SINUSOIDALEASEOUT:		return "SinusoidalEaseOut";
		case SINUSOIDALEASEIN:		return "SinusoidalEaseIn";
		case SINUSOIDALEASEINOUT:	return "SinusoidalEaseInOut";

		case EXPONENTIALEASEOUT:	return "ExponentialEaseOut";
		case EXPONENTIALEASEIN:		return "ExponentialEaseIn";
		case EXPONENTIALEASEINOUT:	return "ExponentialEaseInOut";

		case CIRCULAREASEOUT:		return "CircularEaseOut";
		case CIRCULAREASEIN:		return "CircularEaseIn";
		case CIRCULAREASEINOUT:		return "CircularEaseInOut";

		default:  
		return "LinearInterpolation";
	}
}




float Curve::LinearInterpolation(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    return t * end + (1.f - t) * start;
}

float Curve::QuadraticEaseOut(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    //return   -end * t * (t - 2.f) - 1.f;
	return -end * t * (t - 2) + start; // FIX BY AARON
}
float Curve::QuadraticEaseIn(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    //return end * t * t + start - 1.f;
	return end*t*t + start;
}
float Curve::QuadraticEaseInOut(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    t *= 2.f;
    if (t < 1.f) return end/2.f * t * t + start;
    t--;
    return -end/2.f * (t*(t-2) - 1) + start;
}

float Curve::CubicEaseOut(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    t -= 1;
    return end*(t * t * t + 1.f) + start;
}
float Curve::CubicEaseIn(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    return end * t * t * t+ start;
}
float Curve::CubicEaseInOut(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    t *= 2.;
    if (t < 1.) return end/2 * t * t * t + start;
    t -= 2;
    return end/2*(t * t * t + 2) + start;
}

float Curve::QuarticEaseOut(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    t--;
    return -end * (t * t * t * t - 1) + start;
}
float Curve::QuarticEaseIn(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    return end * t * t * t * t + start;
}
float Curve::QuarticEaseInOut(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    t *= 2.f;
    if (t < 1.f) 
        return end/2.f * t * t * t * t + start;
    t -= 2.f;
    return -end/2.f * (t * t * t * t - 2.f) + start;
}

float Curve::QuinticEaseOut(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    t--;
    return end * (t * t * t * t * t + 1) + start;
}
float Curve::QuinticEaseIn(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    return end * t * t * t * t * t + start;
}
float Curve::QuinticEaseInOut(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    t *= 2.f;
    if (t < 1.f) 
        return end/2 * t * t * t * t * t + start;
    t -= 2;
    return end/2 * ( t * t * t * t * t + 2) + start;
}

float Curve::SinusoidalEaseOut(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    return end * sinf(t * (M_PI/2)) + start;
}
float Curve::SinusoidalEaseIn(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    return -end * cosf(t * (M_PI/2)) + end + start;
}
float Curve::SinusoidalEaseInOut(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    return -end/2.f * (cosf(M_PI*t) - 1.f) + start;
}

float Curve::ExponentialEaseOut(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    return end * (-powf(2.f, -10.f * t) + 1.f ) + start;
}
float Curve::ExponentialEaseIn(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    return end * powf(2.f, 10.f * (t - 1.f) ) + start;
}
float Curve::ExponentialEaseInOut(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    t *= 2.f;
    if (t < 1.f) 
        return end/2.f * powf(2.f, 10.f * (t - 1.f) ) + start;
    t--;
    return end/2.f * ( -powf(2.f, -10.f * t) + 2.f ) + start;
}

float Curve::CircularEaseOut(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    t--;
    return end * sqrtf(1.f - t * t) + start;
}
float Curve::CircularEaseIn(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    return -end * (sqrtf(1.f - t * t) - 1.f) + start;
}
float Curve::CircularEaseInOut(float t, float start, float end)
{
    BoundsCheck(t, start, end);
    t *= 2.f;
    if (t < 1.f) 
        return -end/2.f * (sqrtf(1.f - t * t) - 1.f) + start;
    t -= 2.f;
    return end/2.f * (sqrtf(1.f - t * t) + 1.f) + start;
}