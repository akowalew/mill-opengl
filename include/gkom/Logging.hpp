#pragma once

#include <cstdio>
#include <string>

namespace gkom {

class Logger
{
public:
	explicit Logger(std::string_view name);

	void operator()(std::string_view str);

private:
	std::string name_;
};

class Logging
{
public:
	static Logger& getLogger(std::string_view name);
};

} // gkom
