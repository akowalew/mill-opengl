#pragma once

#include <variant>

namespace gkom {

enum class KeyCode
{
	Escape = 256,
	Enter = 257,
	Right = 262,
	Left = 263,
	Down = 264,
	Up = 265,
};

enum class KeyAction
{
	Press,
	Release,
	Repeat
};

struct KeyEvent
{
	KeyCode code;
	KeyAction action;
};

struct SizeEvent
{
	int width;
	int height;
};

using Event =
	std::variant<
		KeyEvent,
		SizeEvent
	>;

} // gkom
