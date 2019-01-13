#include "gkom/geometry/Pyramid.hpp"

namespace gkom {
namespace geometry {

Pyramid::Pyramid()
{

}

float Pyramid::width() const
{
	return width_;
}

void Pyramid::setWidth(float width)
{
	width_ = width;
}

float Pyramid::height() const
{
	return height_;
}

void Pyramid::setHeight(float height)
{
	height_ = height;
}

float Pyramid::length() const
{
	return length_;
}

void Pyramid::setLength(float length)
{
	length_ = length;
}

} // geometry
} // gkom

// #include "Pyramid.hpp"

// #include <array>
// #include <tuple>

// namespace {

// using Position = std::array<GLfloat, 3>;
// using Color = std::array<GLfloat, 3>;
// using Texcoord = std::array<GLfloat, 2>;

// struct Vertex
// {
// 	Position position;
// 	Color color;
// 	Texcoord texcoord;
// };

// Vertex Vertices[] = {
//     {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
//     {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
//     {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
//     {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
//     {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
//     {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},

//     {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
//     {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
//     {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
//     {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
//     {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
//     {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},

//     {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
//     {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
//     {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
//     {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
//     {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
//     {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},

//     {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
//     {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
//     {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
//     {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
//     {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
//     {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},

//     {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
//     {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
//     {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
//     {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
//     {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
//     {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

//     {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
//     {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
//     {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
//     {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
//     {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
//     {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
// };

// } //

// Rectangle::Rectangle()
// 	:	vao{}
// 	,	vbo{Vertices, GL_STATIC_DRAW}
// 	,	vsh{"res/Pyramid.vsh"}
// 	,	fsh{"res/Pyramid.fsh"}
// 	,	program{vsh, fsh}
//     ,	positionAttr{program.getAttribute("position")}
//     ,	colorAttr{program.getAttribute("color")}
//     ,	texcoordAttr{program.getAttribute("texcoord")}
//     ,   modelUni{program.getAttribute("model")}
//     ,   viewUni{program.getAttribute("view")}
//     ,   projUni{program.getAttribute("proj")}
//     ,	iipwTex{"res/iipw.png", GL_TEXTURE0}
// {
// 	const auto format = GL_FLOAT;
// 	const auto normalize = GL_FALSE;
// 	const auto stride = sizeof(Vertex);
// 	positionAttr.setFormat(std::tuple_size_v<Position>,
// 						   format, normalize,
//     	                   stride, offsetof(Vertex, position));
//    	colorAttr.setFormat(std::tuple_size_v<Color>,
//    		                format, normalize,
//     	                stride, offsetof(Vertex, color));
//    	texcoordAttr.setFormat(std::tuple_size_v<Texcoord>,
//    		                   format, normalize,
//     	                   stride, offsetof(Vertex, texcoord));

// 	positionAttr.enable();
// 	colorAttr.enable();
// 	texcoordAttr.enable();

// 	iipwTex.bind();
//     iipwTex.setParams({{GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE},
//                        {GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE},
//                        {GL_TEXTURE_MIN_FILTER, GL_LINEAR},
//                        {GL_TEXTURE_MAG_FILTER, GL_LINEAR}});
// 	program.getUniform("texIIPW").setValue(0);
// }

// void
// Rectangle::draw()
// {
// 	vao.bind();
// 	program.use();
// 	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
// }



            // auto view = glm::lookAt(cameraPosition, centerPoint, upAxis);
            // viewUni.setValue(view, GL_FALSE);

            // auto proj = glm::perspective(fieldOfView, aspectRatio,
            //                              nearPlane, farPlane);
            // projUni.setValue(proj, GL_FALSE);

            // auto timeNow = high_resolution_clock::now();
            // auto timeDiff = duration_cast<duration<float>>(timeNow - startTime).count();
            // auto model = glm::rotate(glm::mat4{1.0f},
            //                          0.5f * timeDiff * glm::radians(180.0f),
            //                          glm::vec3(0.0f, 0.0f, 1.0f));
            // modelUni.setValue(model, GL_FALSE);

            // glDrawArrays(GL_TRIANGLES, 0, 36);

