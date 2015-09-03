/**
*		@class BezierPath														 
*																			 
*		@brief	Bezier Path class													 
*																			 
*		@author Shane Coates												 
*																			 
*		@date 19/06/2014													 
*/

#ifndef	BEZIER_PATH_H
#define BEZIER_PATH_H

#include <vector>
#include "MathLib.h"

#define SEGMENTS_PER_CURVE 100
class Framework;
class BezierPath
{
public:

	BezierPath(Framework* framework, Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3);
	~BezierPath();

	Vec2 CalculateBezierPoint(float t, Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3);
 
	std::vector<Vec2 > GetDrawingPoints();

	void AddDrawingPoint(Vec2 point);
	void ClearDrawingPoints();

	void Draw();
	void Draw(Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3);

	static void DrawNew(Framework* framework, Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3);

private:

	std::vector<Vec2 > controlPoints;

	float m_t; 
	Vec2 m_p0;
	Vec2 m_p1;
	Vec2 m_p2;
	Vec2 m_p3;

	Framework* m_framework;

};

#endif