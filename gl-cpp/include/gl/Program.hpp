#pragma once

#include <cassert>
#include <cstdio>
#include <utility>
#include <vector>
#include <functional>
#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>

#include "gl/Shader.hpp"
#include "gl/Attribute.hpp"
#include "gl/Uniform.hpp"

namespace gl {

class Program
{
public:
	using Handle = GLuint;

	Program()
		:	handle(createNative())
	{
		// Preconditions
		assert(handle);
	}

	Program(std::initializer_list<std::reference_wrapper<Shader>> shaders)
		:	Program()
	{
		for(auto& shader : shaders)
		{
			attach(shader);
		}

		link();
		use();
	}

	~Program()
	{
		if(handle)
		{
			puts("[GL] Deleting program...");
			glDeleteProgram(handle);
		}
	}

	Program(Program&& other)
	{
		*this = std::move(other);
	}

	Program&
	operator=(Program&& other)
	{
		handle = other.handle;
		other.handle = Handle{};
		return *this;
	}

	void attach(Shader& shader)
	{
		puts("[GL] Attaching shader...");
		glAttachShader(handle, shader);
	}

	void detach(Shader& shader)
	{
		puts("[GL] Detaching shader...");
		glDetachShader(handle, shader);
	}

	void link()
	{
		puts("[GL] Linking program...");
		glLinkProgram(handle);

		GLint linked;
		glGetProgramiv(handle, GL_LINK_STATUS, &linked);
		if(!linked)
		{
		    GLsizei logLength = 0;
			glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &logLength);

			std::vector<GLchar> log(logLength);
		    glGetProgramInfoLog(handle, log.size(), nullptr, log.data());
		    printf("[GL] Could not link program. Error: '%.*s'\n",
		    	logLength, log.data());

		    throw std::runtime_error("Could not link program");
		}
	}

	void use()
	{
		glUseProgram(handle);
	}

	Attribute getAttribute(const GLchar* name)
	{
		printf("[GL] Getting attribute location... Name: '%s'\n", name);
		const auto location = glGetAttribLocation(handle, name);
		if(location == -1)
		{
			throw std::runtime_error("Could not get location of attribute");
		}

		return Attribute{location};
	}

	Uniform getUniform(const GLchar* name)
	{
		printf("[GL] Getting uniform location... Name: '%s'\n", name);
		const auto location = glGetUniformLocation(handle, name);
		if(location == -1)
		{
			throw std::runtime_error("Could not get location of uniform");
		}

		return Uniform{location};
	}

	operator Handle() const noexcept { return handle; }

private:
	Handle createNative()
	{
		puts("[GL] Creating program...");
		handle = glCreateProgram();
		if(!handle)
		{
			throw std::runtime_error("Could not create program");
		}

		return handle;
	}

	Handle handle;
};

} // gl
