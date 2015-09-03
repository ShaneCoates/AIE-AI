/*---------------------------------------------------------------------------*/
/*																			 */	
/*				Author:			Shane Coates								 */
/*				Description:	Sprite Batch Factory						 */
/*																			 */
/*---------------------------------------------------------------------------*/

#ifndef GAME_H
#define GAME_H

#include "GL\glew.h"
#include "SpriteBatch.h"
#include <MathLib.h>
#include <vector>

class GLFWwindow;

class Texture2D;
class Framework;

struct ColorVertex
{
	ColorVertex(float x, float y, float r, float g, float b, float a)
	{
		vPosition[0] = x;
		vPosition[1] = y;
		vPosition[2] = 0;
		vPosition[3] = 1;

		vColour[0] = r;
		vColour[1] = g;
		vColour[2] = b;
		vColour[3] = a;
	}

	float vPosition[4];		// this could be a vec4. or, a vec3 + float... represents x y z w.
	float vColour[4];		// represents red, green, blue, alpha.
};

struct VertexUVColor
{
	VertexUVColor(float x, float y, float u, float v, float r, float g, float b, float a)
	{
		vPosition[0] = x;
		vPosition[1] = y;
		vPosition[2] = 0;
		vPosition[3] = 1;

		vUV[0] = u;
		vUV[1] = v;

		vColour[0] = r;
		vColour[1] = g;
		vColour[2] = b;
		vColour[3] = a;
	}

	VertexUVColor(Vec3 pos, Vec2 uv, Vec4 color)
	{
		vPosition[0] = pos.x;
		vPosition[1] = pos.y;
		vPosition[2] = 0;
		vPosition[3] = 1;

		vUV[0] = uv.x;
		vUV[1] = uv.y;

		vColour[0] = color.r;
		vColour[1] = color.g;
		vColour[2] = color.b;
		vColour[3] = color.a;
	}

	float vPosition[4];		// this could be a vec4. or, a vec3 + float... represents x y z w.
	float vUV[2];			// represents texture coords
	float vColour[4];		// represents red, green, blue, alpha.
};

struct LineSegment_t
{
  Vec2 point1;
  Vec4 colour1;
  Vec2 point2;
  Vec4 colour2;
};


class SpriteBatch_NonImmediate : public SpriteBatch
{
public:
	SpriteBatch_NonImmediate(Framework *pFramework);
	virtual ~SpriteBatch_NonImmediate();

	virtual void Begin();
	virtual void End();

	virtual void DrawSprite(Texture2D* pTexture, const Vec2& position, bool centered);
	virtual void DrawSprite(Texture2D* pTexture, const Mat3x3& transform, bool centered);
	virtual void DrawSprite(Texture2D* pTexture, const Vec2& scale, const Mat3x3& transform, bool centered, Vec4 UV);
	virtual void DrawLine(const Vec2& pointA, const Vec2& pointB, const Vec4& colour);
	virtual void DrawPoint(const Vec2& point, const Vec4& colour);
	virtual void DrawQuad(const Mat3x3& transform, bool centered, const Vec4& colour);


	GLuint GetShaderProgram() { return m_shader; }

	// builds is an OpenGL Shader Program...
	// a_vertex and a_frag refer to filenames for our vertex and fragment shader source files.
	static GLuint CreateProgram(const char *a_vertex, const char *a_frag);

	// Create shader used only within the Create Program function
	static GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);

private:

	// load / unload buffers and shaders
	void Load();
	void Unload();

	GLuint m_shader;
	GLuint m_flatShader;
	GLuint m_flatQuadShader;


	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;

	GLuint m_lineVAO;
	GLuint m_lineVBO;
	GLuint m_lineIBO;


	Mat4x4 m_Projection;
};

#endif