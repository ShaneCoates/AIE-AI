/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	Base 2d textureclass

-----------------------------------------------------------------------------*/

#ifndef TEXTURE2D_H
#define	TEXTURE2D_H

#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <MathLib.h>
#include <iostream>
#include "Asset.h"

class Vec2;
class Vec3;

class Texture2D : public TAsset<Texture2D>
{
public:

	Texture2D(const char* filename, bool repeated = false);

	virtual ~Texture2D();

	unsigned int GetWidth() const;

	unsigned int GetHeight() const;

	GLuint GetTextureHandle() const;

protected:
private:

	GLuint m_spriteID;

	char* m_spriteAddress;

	unsigned int m_width;
	unsigned int m_height;
};


#endif