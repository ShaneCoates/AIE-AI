/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	Font Renderer class

-----------------------------------------------------------------------------*/

#ifndef FONTRENDERER_H
#define	FONTRENDERER_H

#include <freetype-gl\freetype-gl.h>
#include <map>
#include <string>

class Vec2;
class Vec4;

class GLFontRenderer
{
public:
	GLFontRenderer();
	~GLFontRenderer();

	void LoadFont(std::string fontName, std::string filePath, float fontSize);

	void DrawString(std::string fontName, std::string text, const Vec2& position);
	void DrawString(std::string fontName, std::string text, const Vec2& position, const Vec4& colour);

	bool IsFontLoaded(std::string fontName);

private:
	std::map<std::string, texture_font_t *> m_LoadedFonts;
	texture_atlas_t *m_FontAtlas;

	static const std::string DEFAULT_LOADED_GLYPHS;
	static const int FONT_ATLAS_WIDTH;
	static const int FONT_ATLAS_HEIGHT;
};


#endif