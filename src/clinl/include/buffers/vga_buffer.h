#pragma once
#include "buffers/buffer.hpp"
#include <stdint.h>

namespace VGA
{

/* Hardware text mode color constants. */
enum class color : uint8_t
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHT_GREY = 7,
	DARK_GREY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	LIGHT_MAGENTA = 13,
	LIGHT_BROWN = 14,
	WHITE = 15,
};

struct color_mode
{
	uint8_t v;
	constexpr color_mode(const uint8_t _v = (uint8_t)color::WHITE) : v(_v){};
} __attribute__((packed));

constexpr inline color_mode make_color_mode(color fg, color bg = color::BLACK)
{
	return ((uint8_t)fg | (uint8_t)bg << 4);
}

/* Hardware text mode character */
struct character
{
	constexpr character(char ch = ' ', color fg = color::WHITE, color bg = color::BLACK)
		: c(ch), color(make_color_mode(fg, bg))
	{
	}

	constexpr character(char ch, color_mode tcolor)
		: c(ch), color(tcolor)
	{
	}

	char c;
	color_mode color;
} __attribute__((packed));

void initialize();

extern ksdk::buffer<char> buffer;
extern ksdk::buffer<character> text_buffer;
extern size_t TEXT_WIDTH;
extern size_t TEXT_HEIGHT;
extern size_t text_cursor;
extern color_mode text_color;
} // namespace VGA