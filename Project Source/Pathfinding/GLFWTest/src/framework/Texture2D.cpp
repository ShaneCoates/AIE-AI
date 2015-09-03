#include "Texture2D.h"

Texture2D::Texture2D(const char* filename, bool repeated) : TAsset<Texture2D>(filename)
{
	int fileNameLength = strlen(filename) + 1;

	m_spriteAddress = new char[fileNameLength];
	strcpy_s(m_spriteAddress, fileNameLength, filename ); 

	int width, height, channels;

	unsigned char *imageData = SOIL_load_image
	(
		filename,
		&width,
		&height,
		&channels,
		SOIL_LOAD_AUTO
	);

	if(imageData == NULL)
	{
		throw std::exception((std::string("Image data was not loaded: ") + std::string(filename)).c_str());
	}

	m_spriteID = SOIL_create_OGL_texture
	(
		imageData,
		width,
		height,
		channels,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
	);
	if(repeated)
	{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	SOIL_free_image_data(imageData);

	m_width = width;
	m_height = height;

}

Texture2D::~Texture2D()
{
	//glDeleteTextures(1, &m_spriteID);
}

unsigned int Texture2D::GetWidth() const
{
	return m_width;
}

unsigned int Texture2D::GetHeight() const
{
	return m_height;
}

GLuint Texture2D::GetTextureHandle() const
{
	return m_spriteID;
}
