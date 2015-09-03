#include "FontRenderer.h"
#include "Vec2.h"
#include "Vec4.h"
#include <GL\glew.h>
#include <GLFW/glfw3.h>

const std::string GLFontRenderer::DEFAULT_LOADED_GLYPHS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*():";
const int GLFontRenderer::FONT_ATLAS_WIDTH = 1024;
const int GLFontRenderer::FONT_ATLAS_HEIGHT = 1024;

GLFontRenderer::GLFontRenderer()
{
	m_FontAtlas = texture_atlas_new(FONT_ATLAS_WIDTH, FONT_ATLAS_HEIGHT, 3);
}

GLFontRenderer::~GLFontRenderer()
{
	for(auto itr = m_LoadedFonts.begin(); itr != m_LoadedFonts.end(); ++itr)
	{
		texture_font_delete(itr->second);
	}

	texture_atlas_delete(m_FontAtlas);

	m_LoadedFonts.clear();
}

void GLFontRenderer::LoadFont(std::string fontName, std::string filePath, float fontSize)
{
	texture_font_t *font = texture_font_new_from_file(m_FontAtlas, fontSize, filePath.c_str());
	m_LoadedFonts[fontName] = font;

	std::wstring w_glyphs(DEFAULT_LOADED_GLYPHS.begin(), DEFAULT_LOADED_GLYPHS.end());
	texture_font_load_glyphs(font, w_glyphs.c_str());
}

void GLFontRenderer::DrawString(std::string fontName, std::string text, const Vec2& position)
{
	DrawString(fontName, text, position, Vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void GLFontRenderer::DrawString(std::string fontName, std::string text, const Vec2& position, const Vec4& colour)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glBindTexture(GL_TEXTURE_2D, m_FontAtlas->id);

	auto font = m_LoadedFonts[fontName];
	float kerning = 0;

	Vec2 pen = position;

	glBegin(GL_QUADS);

	for(unsigned int i = 0; i < text.length(); i++)
	{
		auto glyph = texture_font_get_glyph(font, text[i]);

		if(glyph != NULL)
		{
			// get kerning (space between characters)
			if(i > 0)
			{
				kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
			}

			// move pen by spacing
			pen.x += kerning;

			// get vertex positions
			float x0 = ( pen.x + glyph->offset_x );
			float y0 = ( pen.y + glyph->offset_y );
			float x1 = ( x0 + glyph->width );
			float y1 = ( y0 + glyph->height );

			// get texture UV
			float s0 = glyph->s0;
			float t0 = glyph->t0;
			float s1 = glyph->s1;
			float t1 = glyph->t1;

			
			// setup quads
			glColor4f(colour.r, colour.g, colour.b, colour.a);

			glTexCoord2f(s0, t1); glVertex3f(x0, y0, 0.0f);
			glTexCoord2f(s0, t0); glVertex3f(x0, y1, 0.0f);
			glTexCoord2f(s1, t0); glVertex3f(x1, y1, 0.0f);
			glTexCoord2f(s1, t1); glVertex3f(x1, y0, 0.0f);

			pen.x += glyph->advance_x;
		}
	}

	glEnd();
	glDisable(GL_BLEND);
}
	 
bool GLFontRenderer::IsFontLoaded(std::string fontName)
{
	return (m_LoadedFonts.find(fontName) != m_LoadedFonts.end());
}