#include "SpriteBatch_NonImmediate.h"
#include "Texture2D.h"
#include "GLFW/glfw3.h"
#include "Game.h"
#include "Framework.h"
#include <string>
#include <vector>
#include <fstream>

SpriteBatch_NonImmediate::SpriteBatch_NonImmediate(Framework *pFramework) : SpriteBatch(pFramework)
{
	m_pFramework = pFramework;

	Load();
}

SpriteBatch_NonImmediate::~SpriteBatch_NonImmediate()
{
	Unload();
}

void SpriteBatch_NonImmediate::Begin()
{
	glUseProgram(m_shader);

	// generate projection matrix
	m_Projection = Mat4x4::CreateOrthographic(0.0f, (float)m_pFramework->GetWindowWidth(), 0.0f, (float)m_pFramework->GetWindowHeight(), -1.0f, 1.0f);

	// assign to projection uniform
	int projUniformLocation = glGetUniformLocation(m_shader, "projection");

	if(projUniformLocation > -1) {
		glUniformMatrix4fv(projUniformLocation, 1, false, m_Projection.m);
	}

	glUseProgram(0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void SpriteBatch_NonImmediate::End()
{

}

void SpriteBatch_NonImmediate::Load()
{
	//don't worry how the create program function works...
	//just know that it will create our shader and give us an error message if it doesn't
	m_shader = CreateProgram("./shaders/TexturedVertexShader.glsl", "./shaders/TexturedFragmentShader.glsl");
	m_flatShader = CreateProgram("./shaders/FlatVertexShader.glsl", "./shaders/FlatFragmentShader.glsl");
	
	glGenVertexArrays(1, &m_lineVAO);
	glGenBuffers(1, &m_lineVBO);
	glGenBuffers(1, &m_lineIBO);

	//Generate buffers for openGL to store data on the graphics card
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	//Bind the buffers to the appropriate type.
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	// enable attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// set attribute pointers
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertexUVColor), (void *) 0);  // Vec4 pos
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexUVColor), (void *) 16); // Vec2 uv
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(VertexUVColor), (void *) 24); // Vec4 color

	glBindVertexArray(0);
}

void SpriteBatch_NonImmediate::Unload()
{
	glDeleteProgram(m_shader);
	glDeleteProgram(m_flatShader);

	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
	glDeleteBuffers(1, &m_lineVBO);
	glDeleteBuffers(1, &m_lineIBO);
	glDeleteVertexArrays(1, &m_vao);
	glDeleteVertexArrays(1, &m_lineVAO);

}

GLuint SpriteBatch_NonImmediate::CreateShader(GLenum a_eShaderType, const char *a_strShaderFile)
{
	std::string strShaderCode;

	//open shader file
	std::ifstream shaderStream(a_strShaderFile);

	//if that worked ok, load file line by line
	if(shaderStream.is_open())
	{
		std::string Line = "";
		while(std::getline(shaderStream, Line))
		{
			strShaderCode += "\n" + Line;
		}
		shaderStream.close();
	}

	//convert to cstring
	char const *szShaderSourcePointer = strShaderCode.c_str();
	
	//create shader ID
	GLuint uiShader = glCreateShader(a_eShaderType);

	//attach the shader source to our generated shader ID
	glShaderSource(uiShader, 1, &szShaderSourcePointer, NULL);

	//compile shader - GL nust compile the shader source code.
	//as each graphics card is different, instructions may differ on the hardware GPU
	glCompileShader(uiShader);

	//check for compilation errors and output them
	GLint iStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iStatus);

	//if there is an error, print the error to the console window
	if (iStatus == GL_FALSE)
	{

		// how long is the of the error
		GLint infoLogLength;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		// create memory for the error message
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(uiShader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch(a_eShaderType)
		{
			case GL_VERTEX_SHADER:		strShaderType = "vertex"; break;
			case GL_FRAGMENT_SHADER:	strShaderType = "fragment"; break;
		}

		// print the error to the console window.
		printf("Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		
		// remember the memory we created 13 lines above...
		delete[] strInfoLog;
	}

	// return the shader ID...
	return uiShader;
}
GLuint SpriteBatch_NonImmediate::CreateProgram(const char *a_vertex, const char *a_frag)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, a_vertex));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, a_frag));

	//create shader program ID
	GLuint uiProgram = glCreateProgram();

	//attach shaders
	for(auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
		glAttachShader(uiProgram, *shader);

	//link program
	glLinkProgram(uiProgram);

	//check for link errors and output them
	GLint status;
	glGetProgramiv (uiProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(uiProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(uiProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	// now that the program has been built, we can get rid of the individual shaders...
	for(auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glDetachShader(uiProgram, *shader);
		glDeleteShader(*shader);
	}

	// return our compiled shader program.
	return uiProgram;
}

void SpriteBatch_NonImmediate::DrawSprite(Texture2D* pTexture, const Vec2& scale, const Mat3x3& transform, bool centered, Vec4 UV)
{
	glBindVertexArray(m_vao);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	

	int m_width = scale.x;
	int m_height = scale.y;

	Vec3 m_topLeft;		
	Vec3 m_bottomLeft;	
	Vec3 m_bottomRight;	
	Vec3 m_topRight;		

	if(centered)
	{
		m_topLeft			= Vec3(-m_width/2.0f,	-m_height/2.0f, 1.0f) * transform;
		m_bottomLeft		= Vec3(-m_width/2.0f,	 m_height/2.0f, 1.0f) * transform;
		m_bottomRight		= Vec3(m_width/2.0f,	 m_height/2.0f, 1.0f) * transform;
		m_topRight			= Vec3(m_width/2.0f,	-m_height/2.0f, 1.0f) * transform;
	}
	else
	{
		m_topLeft			= Vec3(0.0f,	0.0f,		1.0f) * transform;
		m_bottomLeft		= Vec3(0.0f,	m_height,	1.0f) * transform;
		m_bottomRight		= Vec3(m_width,	m_height,	1.0f) * transform;
		m_topRight			= Vec3(m_width,	0.0f,		1.0f) * transform;
	}


	VertexUVColor verts[4] = 
	{
		VertexUVColor(m_topLeft,		Vec2(UV.z, UV.x), Vec4(m_red, m_green, m_blue, m_alpha)),
		VertexUVColor(m_bottomLeft,		Vec2(UV.z, UV.y), Vec4(m_red, m_green, m_blue, m_alpha)),
		VertexUVColor(m_bottomRight,	Vec2(UV.w, UV.y), Vec4(m_red, m_green, m_blue, m_alpha)),
		VertexUVColor(m_topRight,		Vec2(UV.w, UV.x), Vec4(m_red, m_green, m_blue, m_alpha)),
	};

	GLubyte indicies[6] = 
	{
		0, 1, 2,
		0, 2, 3
	};

	glUseProgram(m_shader);

	// bind texture
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, pTexture->GetTextureHandle());
	
	int textureUniform = glGetUniformLocation(m_shader, "texture");

	if(textureUniform > -1) {
		glUniform1i(textureUniform, 0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexUVColor) * 4, verts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 6, indicies, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);

	glUseProgram(0);
	glBindVertexArray(0);
}

void SpriteBatch_NonImmediate::DrawSprite(Texture2D* pTexture, const Vec2& position, bool centered)
{
	DrawSprite(pTexture, Mat3x3::CreateTranslation(position), centered);
}

void SpriteBatch_NonImmediate::DrawSprite(Texture2D* pTexture, const Mat3x3& transform, bool centered)
{
	DrawSprite(pTexture, Vec2(1.0f, 1.0f), transform, centered, Vec4(0.0f, 1.0f, 0.0f, 1.0f));
}

void SpriteBatch_NonImmediate::DrawLine(const Vec2& pointA, const Vec2& pointB, const Vec4& colour)
{
	glBindVertexArray(m_lineVAO);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	

	glUseProgram(m_flatShader);
	glUniformMatrix4fv(glGetUniformLocation(m_flatShader, "projection"), 1, false, m_Projection.m);

	float data[16] = {
		pointA.x, pointA.y, 0.0f, 1.0f, colour.r, colour.g, colour.b, colour.a,
		pointB.x, pointB.y, 0.0f, 1.0f, colour.r, colour.g, colour.b, colour.a
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_lineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 4, GL_FLOAT, false, sizeof(float) * 8, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(float) * 8, (void *)16);

	glDrawArrays(GL_LINES, 0, 2);


	glUseProgram(0);
	glBindVertexArray(0);
	
}
void SpriteBatch_NonImmediate::DrawPoint(const Vec2& point, const Vec4& colour)
{
	glBindVertexArray(m_lineVAO);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	

	glUseProgram(m_flatShader);
	glUniformMatrix4fv(glGetUniformLocation(m_flatShader, "projection"), 1, false, m_Projection.m);

	float data[8] = {
		point.x, point.y, 0.0f, 1.0f, colour.r, colour.g, colour.b, colour.a,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_lineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 4, GL_FLOAT, false, sizeof(float) * 8, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(float) * 8, (void *)16);

	glDrawArrays(GL_POINTS, 0, 2);
	
	glUseProgram(0);
	glBindVertexArray(0);
}
void SpriteBatch_NonImmediate::DrawQuad(const Mat3x3& transform, bool centered, const Vec4& colour)
{

	Vec3 m_topLeft;		
	Vec3 m_bottomLeft;	
	Vec3 m_bottomRight;	
	Vec3 m_topRight;

	if(centered)
	{
		m_topLeft			= Vec3(-0.5f,	-0.5f, 1.0f) * transform;
		m_bottomLeft		= Vec3(-0.5f,	 0.5f, 1.0f) * transform;
		m_bottomRight		= Vec3(0.5f,	 0.5f, 1.0f) * transform;
		m_topRight			= Vec3(0.5f,	-0.5f, 1.0f) * transform;
	}
	else
	{
		m_topLeft			= Vec3(0.0f,	0.0f,		1.0f) * transform;
		m_bottomLeft		= Vec3(0.0f,	1.0f,		1.0f) * transform;
		m_bottomRight		= Vec3(1.0f,	1.0f,		1.0f) * transform;
		m_topRight			= Vec3(1.0f,	0.0f,		1.0f) * transform;
	}

	ColorVertex verts[4] = 
	{
		ColorVertex(m_topLeft.x, m_topLeft.y, colour.r, colour.g, colour.b, colour.a),
		ColorVertex(m_bottomLeft.x, m_bottomLeft.y, colour.r, colour.g, colour.b, colour.a),
		ColorVertex(m_bottomRight.x, m_bottomRight.y, colour.r, colour.g, colour.b, colour.a),
		ColorVertex(m_topRight.x, m_topRight.y, colour.r, colour.g, colour.b, colour.a),
	};

	GLubyte indicies[6] = 
	{
		0, 1, 2,
		0, 2, 3
	};
	glBindVertexArray(m_lineVAO);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	

	glUseProgram(m_flatShader);
	glUniformMatrix4fv(glGetUniformLocation(m_flatShader, "projection"), 1, false, m_Projection.m);

	glBindVertexArray(m_lineVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_lineVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_lineIBO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void *) 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void *) 16);

	glBufferData(GL_ARRAY_BUFFER, sizeof(ColorVertex) * 4, verts, GL_STATIC_DRAW);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 6, indicies, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);

	glBindVertexArray(0);
	glUseProgram(0);
}