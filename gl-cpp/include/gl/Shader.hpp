#pragma once

#include <cassert>
#include <cstdio>
#include <utility>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>

namespace gl {

class Shader
{
public:
	using Handle = GLuint;

	explicit Shader(GLenum type)
		:	handle(createNative(type))
	{
		// Preconditions
		assert(handle);
	}

	Shader(const char* path, GLenum type)
		:	Shader(type)
	{
		loadFromFile(path);
	}

	~Shader()
	{
		if(handle)
		{
			puts("[GL] Deleting shader...");
			glDeleteShader(handle);
		}
	}

	Shader(Shader&& other)
	{
		*this = std::move(other);
	}

	Shader& operator=(Shader&& other)
	{
		handle = other.handle;
		other.handle = Handle{};
		return *this;
	}

	void loadFromFile(const char* path)
	{
		printf("[GL] Opening file with shader's code... Path: '%s'\n", path);
		auto ifs = std::ifstream{};
		ifs.exceptions(std::ios_base::failbit | std::ios_base::badbit);
		ifs.open(path);

		puts("[GL] Reading shader code from file...");
		auto strs = std::stringstream{};
		strs.exceptions(std::ios_base::failbit | std::ios_base::badbit);
		strs << ifs.rdbuf();
		const auto code = strs.str();

		auto codeData = code.c_str();
		setSource(1, &codeData);
		compile();
	}

	void setSource(GLsizei count, const GLchar** string,
		const GLint* length = nullptr)
	{
		puts("[GL] Setting shader's sources...");
		glShaderSource(handle, count, string, length);
	}

	void compile()
	{
		puts("[GL] Compiling shader...");
		glCompileShader(handle);

		GLint compiled;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);
		if (compiled != GL_TRUE)
		{
		    GLsizei logLength = 0;
			glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLength);

			std::vector<GLchar> log(logLength);
		    glGetShaderInfoLog(handle, log.max_size(), nullptr, log.data());
		    printf("[GL] Could not compile shader. Error: '%.*s'\n",
		    	logLength, log.data());

		    throw std::runtime_error("Could not compile shader");
		}
	}

	operator Handle() const noexcept { return handle; }

private:
	static Handle createNative(GLenum type)
	{
		printf("[GL] Creating shader... Type: %d\n", type);
		auto handle = glCreateShader(type);
		if(!handle)
		{
			throw std::runtime_error("Could not create shader");
		}

		return handle;
	}

	Handle handle = Handle{};
};

} // gl
