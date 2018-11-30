#pragma once

#include "gl/gl.hpp"

class Triangle
{
public:
	Triangle();

	void draw();

private:
	gl::VertexArray vao;
	gl::VertexBuffer vbo;
	gl::ElementBuffer ebo;
	gl::VertexShader vsh;
	gl::FragmentShader fsh;
	gl::Program program;
	gl::Attribute positionAttr;
	gl::Attribute colorAttr;
	gl::Attribute texcoordAttr;
	gl::Texture2D iipwTex;
	gl::Texture2D weitiTex;
};
