/*-----------------------------------------------------------------------------
		Author:			Shane Coates
		Description:	Basic Vector3 Math Lib class
-----------------------------------------------------------------------------*/

#ifndef COLOUR4_H
#define	COLOUR4_H

#include "math.h"

namespace AIE
{
	class Colour4
	{
	public:
		union 
		{
			float rgba[4];
			struct
			{
				float r, g, b, a;
			};
		};

		//overload constructor
		Colour4(float a_r = 0.0f, float a_g = 0.0f, float a_b = 0.0f, float a_a = 0.0f) 
			: r(a_r), g(a_g), b(a_b), a(a_a) {}

		void SetColour(float a_r, float a_g, float a_b, float a_a)
		{
			r = a_r;
			g = a_g;
			b = a_b;
			a = a_a;
		}

	protected:
	private:


	};
}

#endif