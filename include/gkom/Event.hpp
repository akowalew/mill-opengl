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
	Subtract = 333,
	Add = 334,
	A = 65,
	D = 68,
	S = 83,
	Y = 89,
	W = 87,
	Z = 90,
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
