/*
--------------------------
 font.cpp
 Ilya Bobkov KZ 2017 (c)
--------------------------*/
#include "Font.h"

int result = 0;

// Shader sources
const GLchar* shader = R"glsl(
#version 120
attribute vec4 coord;
varying vec2 texcoord;
void main(void) {
gl_Position = vec4(coord.xy, 0, 1);
texcoord = coord.zw;
)glsl";

struct Character
{
    GLuint TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    GLuint Advance;
};

std::map<GLchar, Character> Characters;
GLuint VAO, VBO;

/*
 * ----------------------------------
 *  Конструктор
 * ----------------------------------
 */
Font::Font(const String &fontName)
{
	result = FT_New_Face( ft, fontName.c_str(), 0, &face );

	if ( result == FT_Err_Unknown_File_Format )
		Msg::Error("FreeType: file format error");
	else
	if ( result )
		Msg::Error("FreeType: font not found");

	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < 128; c++)
	{
		if(FT_Load_Char(face, c, FT_LOAD_RENDER))
	    	Msg::Error("Font: Glyph loading symbol %d error!", c);
			GLuint texture;
		    //glGenTextures(1, &texture);
		    //glBindTexture(GL_TEXTURE_2D, texture);
		    /*glTexImage2D(
		            GL_TEXTURE_2D,
		            0,
		            GL_RED,
		            face->glyph->bitmap.width,
		            face->glyph->bitmap.rows,
		            0,
		            GL_RED,
		            GL_UNSIGNED_BYTE,
		            face->glyph->bitmap.buffer
		        );*/

		        // Set texture options
		        /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/

		        Character character =
		        { 	texture,
		            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
		            glm::ivec2(face->glyph->bitmap_left,  face->glyph->bitmap_top),
		            (ulong)face->glyph->advance.x // FIXIT
		        };

		        Characters.insert(std::pair<GLchar, Character>(c, character));
		    }

		    FT_Done_Face(face);
		    FT_Done_FreeType(ft);

			//glBindTexture(GL_TEXTURE_2D, 0);

		   /* glGenVertexArrays(1, &VAO);
		    glGenBuffers(1, &VBO);
		    glBindVertexArray(VAO);
		    glBindBuffer(GL_ARRAY_BUFFER, VBO);
		    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		    glEnableVertexAttribArray(0);
		    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		    glBindBuffer(GL_ARRAY_BUFFER, 0);
		    glBindVertexArray(0);*/
}

Font::~Font(){
}

//void Font::RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
void Font::RenderText(String text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    // Activate corresponding render state
    //shader.Use();
    //glUniform3f(glGetUniformLocation(shader.Program, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;

        GLfloat vertices[6][4] =
        {
            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }
        };

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (ch.Advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
