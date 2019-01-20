#include "gkom/Logging.hpp"

#include <cassert>
#include <unordered_map>

namespace gkom {

namespace {

std::unordered_map<std::string, Logger> loggers_;

} //

Logger::Logger(std::string_view name)
	:	name_(name)
{}

Logger& Logging::getLogger(std::string_view name)
{
	auto pos = loggers_.find(name.data());
	if(pos == loggers_.end())
	{
		pos = loggers_.emplace_hint(pos,
									std::piecewise_construct,
									std::forward_as_tuple(name),
									std::forward_as_tuple(name));

		assert(pos != loggers_.end());
	}

	return pos->second;
}

void Logger::operator()(std::string_view str)
{
	printf("[%s] %s\n", name_.data(), str.data());
}

} // gkom
