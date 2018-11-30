#include "Triangle.hpp"

#include <array>

namespace {

using Position = std::array<GLfloat, 2>;
using Color = std::array<GLfloat, 3>;
using Texcoord = std::array<GLfloat, 2>;

struct Vertex
{
	Position position;
	Color color;
	Texcoord texcoord;
};

Vertex Vertices[] = {
    {{ 0.0f,  0.5f}, {1.0f, 0.0f, 0.0f}, {4.0f, 0.0f}}, // Top
    {{-0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 4.0f}}, // Bottom-left
    {{ 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {4.0f, 4.0f}}, // Bottom-right
};

GLuint Elements[] = {
    0, 1, 2,
};

} //

Triangle::Triangle()
	:	vao{}
	,	vbo{Vertices, GL_STATIC_DRAW}
	,	ebo{Elements, GL_STATIC_DRAW}
	,	vsh{"res/Triangle.vsh"}
	,	fsh{"res/Triangle.fsh"}
	,	program{vsh, fsh}
    ,	positionAttr{0}
    ,	colorAttr{1}
    ,	texcoordAttr{2}
    ,	iipwTex{"res/iipw.png", GL_TEXTURE0}
    ,	weitiTex{"res/weiti.png", GL_TEXTURE1}
{
	const auto format = GL_FLOAT;
	const auto normalize = GL_FALSE;
	const auto stride = sizeof(Vertex);
	positionAttr.setFormat(std::tuple_size<Position>::value, format, normalize,
    	                   stride, offsetof(Vertex, position));
   	colorAttr.setFormat(std::tuple_size<Color>::value, format, normalize,
    	                   stride, offsetof(Vertex, color));
   	texcoordAttr.setFormat(std::tuple_size<Texcoord>::value, format, normalize,
    	                   stride, offsetof(Vertex, texcoord));

	positionAttr.enable();
	colorAttr.enable();
	texcoordAttr.enable();

	iipwTex.bind();
	iipwTex.setParams({{GL_TEXTURE_WRAP_S, GL_REPEAT},
				       {GL_TEXTURE_WRAP_T, GL_REPEAT},
			           {GL_TEXTURE_MIN_FILTER, GL_LINEAR},
	                   {GL_TEXTURE_MAG_FILTER, GL_LINEAR}});
	program.getUniform("texIIPW").setValue(0);

	weitiTex.bind();
	weitiTex.setParams({{GL_TEXTURE_WRAP_S, GL_REPEAT},
				        {GL_TEXTURE_WRAP_T, GL_REPEAT},
			            {GL_TEXTURE_MIN_FILTER, GL_LINEAR},
	                    {GL_TEXTURE_MAG_FILTER, GL_LINEAR}});
    program.getUniform("texWEITI").setValue(1);
}

void
Triangle::draw()
{
	vao.bind();
	program.use();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
