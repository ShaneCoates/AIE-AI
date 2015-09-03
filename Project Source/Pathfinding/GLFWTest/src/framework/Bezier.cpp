#include "framework/Bezier.h"
#include "framework/framework.h"

BezierPath::BezierPath(Framework* framework, Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3)
{
	m_framework = framework;
	m_p0 = p0;
	m_p1 = p1;
	m_p2 = p2;
	m_p3 = p3;
}

BezierPath::~BezierPath()
{

}

void BezierPath::Draw()
{
	Vec2 q0 = CalculateBezierPoint(0, m_p0, m_p1, m_p2, m_p3);
	for(int i = 1; i <= SEGMENTS_PER_CURVE; i++)
	{
		float t = i / (float) SEGMENTS_PER_CURVE;
		Vec2 q1 = CalculateBezierPoint(t, m_p0, m_p1, m_p2, m_p3);
		m_framework->DrawLine(q0, q1, Vec4(1, 1, 1, 1));
		q0 = q1;
	}
}

void BezierPath::Draw(Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3)
{
	Vec2 q0 = CalculateBezierPoint(0, p0, p1, p2, p3);
	for(int i = 1; i <= SEGMENTS_PER_CURVE; i++)
	{
		float t = i / (float) SEGMENTS_PER_CURVE;
		Vec2 q1 = CalculateBezierPoint(t, p0, p1, p2, p3);
		m_framework->DrawLine(q0, q1, Vec4(1, 1, 1, 1));
		q0 = q1;
	}
}

Vec2 BezierPath::CalculateBezierPoint(float t, Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3)
{
	float u = 1 - t;
	float tt = t*t;
	float uu = u*u;
	float uuu = uu * u;
	float ttt = tt * t;
 
	Vec2 p = p0 * uuu; //first term
	p += p1 * 3 * uu * t; //second term
	p += p2 * 3 * u * tt; //third term
	p += p3 * ttt; //fourth term
 
	return p;
}
 
std::vector<Vec2 > BezierPath::GetDrawingPoints()
{
    std::vector<Vec2 > drawingPoints;
	if(controlPoints.size() < 4)
		return drawingPoints;
    for(int i = 0; i < controlPoints.size() - 3; i+=3)
    {
      Vec2 p0 = controlPoints[i];
      Vec2 p1 = controlPoints[i + 1];
      Vec2 p2 = controlPoints[i + 2];
      Vec2 p3 = controlPoints[i + 3];    
 
      if(i == 0) //Only do this for the first endpoint.
                 //When i != 0, this coincides with the end
                 //point of the previous segment
      {
        drawingPoints.push_back(CalculateBezierPoint(0, p0, p1, p2, p3));
      }    
 
      for(int j = 1; j <= SEGMENTS_PER_CURVE; j++)
      {
        float t = j / (float) SEGMENTS_PER_CURVE;
        drawingPoints.push_back(CalculateBezierPoint(t, p0, p1, p2, p3));
      }
    }
 
    return drawingPoints;
}

void BezierPath::AddDrawingPoint(Vec2 point)
{
	controlPoints.push_back(point);
}

void BezierPath::ClearDrawingPoints()
{
	controlPoints.clear();
}

void BezierPath::DrawNew(Framework *framework, Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3)
{
	float t = 0;
	float u = 1 - t;
	float tt = t*t;
	float uu = u*u;
	float uuu = uu * u;
	float ttt = tt * t;
 
	Vec2 p = p0 * uuu; //first term
	p += p1 * 3 * uu * t; //second term
	p += p2 * 3 * u * tt; //third term
	p += p3 * ttt; //fourth term
 

	Vec2 q0 = p;
	for(int i = 1; i <= SEGMENTS_PER_CURVE; i++)
	{
		float t = i / (float) SEGMENTS_PER_CURVE;
		float u = 1 - t;
		float tt = t*t;
		float uu = u*u;
		float uuu = uu * u;
		float ttt = tt * t;

		Vec2 q1 = p0 * uuu; //first term
		q1 += p1 * 3 * uu * t; //second term
		q1 += p2 * 3 * u * tt; //third term
		q1 += p3 * ttt; //fourth term

		framework->DrawLine(q0, q1, Vec4(1, 1, 1, 1));
		q0 = q1;
	}
}