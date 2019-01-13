#pragma once

#include "gkom/Mesh.hpp"

namespace gkom {
namespace geometry {

class Box
	:	public Mesh
{
public:
	Box();

	float width() const;

	void setWidth(float width);

	float height() const;

	void setHeight(float height);

	float length() const;

	void setLength(float length);

private:
	// gl::VertexArray vao;
	// gl::VertexBuffer vbo;
	// gl::VertexShader vsh;
	// gl::FragmentShader fsh;
	// gl::Program program;
	// gl::Attribute positionAttr;
	// gl::Attribute colorAttr;
	// gl::Attribute texcoordAttr;
	// gl::Uniform modelUni;
	// gl::Uniform viewUni;
	// gl::Uniform projUni;
	// gl::Texture2D iipwTex;
	// gl::Texture2D weitiTex;

	float width_ = 0.0f;
	float height_ = 0.0f;
	float length_ = 0.0f;
};

} // geometry
} // gkom
