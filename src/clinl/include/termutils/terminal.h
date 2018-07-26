#pragma once
#include "buffers/vga_buffer.h"
#include "buffers/string_view"
#include "libk/string.h"
namespace Termutils
{

void initialize();

inline void putchar(const VGA::character character)
{
	if (VGA::text_cursor >= VGA::text_buffer.size())
	{
		auto line_minus_one = VGA::text_buffer.size() - VGA::TEXT_WIDTH;
		memmove(
			VGA::text_buffer.begin(),
			VGA::text_buffer.begin() + VGA::TEXT_WIDTH,
			line_minus_one * sizeof(VGA::character));
		VGA::text_cursor = line_minus_one;
		auto last_line = ksdk::buffer<VGA::character>(VGA::text_buffer.begin() + line_minus_one, VGA::TEXT_WIDTH);
		for (VGA::character &c : last_line)
			c = VGA::character(' ', VGA::text_color);
	}
	switch (character.c)
	{
	case '\n':
		VGA::text_buffer[VGA::text_cursor] = VGA::character(' ', character.color);
		VGA::text_cursor += VGA::TEXT_WIDTH;
		VGA::text_cursor -= VGA::text_cursor % VGA::TEXT_WIDTH;
		break;
	case '\t':
	{
		int advance = (4 - VGA::text_cursor % 4);
		auto begin = &VGA::text_buffer[VGA::text_cursor];
		auto end = begin + advance;
		for (auto it = begin; it != end; ++it)
		{
			*it = VGA::character(' ', character.color);
		}
		VGA::text_cursor += advance;
	}
	break;
	default:
		VGA::text_buffer[VGA::text_cursor] = character;
		++VGA::text_cursor;
		break;
	}
}
inline void putchar(const char c)
{
	putchar(VGA::character(c, VGA::text_color));
}

inline void write(const char *str, size_t size)
{
	auto begin = str;
	auto end = str + size;
	for (auto it = begin; it != end; ++it)
	{
		putchar(*it);
	}
}

struct endl_t
{
};

class terminal_output
{
	friend void Termutils::initialize();

  public:
	enum class int_mode
	{
		bin = 2,
		dec = 10,
		hex = 16
	};
	int_mode mode;
	template <typename T>
	terminal_output &operator<<(const T number)
	{
		const int local_size = 64;
		static char local[local_size] = {};
		static const char digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
		int base = (int)mode;
		auto degree = 1;
		int sign = 1;
		if ((T)(-1) < 0)
		{
			auto trem = number;
			sign = trem < 0 ? -1 : 1;
			unsigned long long rem;
			if (base == 10)
				rem = trem * sign;
			else
				rem = (unsigned long long)trem;
			do
			{
				auto degrad = rem % base;
				local[local_size - degree] = digits[degrad];
				rem -= degrad;
				rem = rem / base;
				degree++;
			} while (rem != 0);
		}
		else
		{
			auto rem = number;
			do
			{
				int degrad = rem % base;
				local[local_size - degree] = digits[degrad];
				rem -= degrad;
				rem /= base;
				degree++;
			} while (rem != 0);
		}
		if (sign == -1 && base == 10)
		{
			local[local_size - degree] = '-';
			degree++;
		}
		else if (base == 2)
		{
			local[local_size - degree] = 'b';
			degree++;
			local[local_size - degree] = '0';
			degree++;
		}
		else if (base == 16)
		{
			local[local_size - degree] = 'x';
			degree++;
			local[local_size - degree] = '0';
			degree++;
		}
		Termutils::write(local + local_size - degree + 1, degree - 1);
		return *this;
	}
};

extern terminal_output cout;
extern size_t tab_size;
extern endl_t endl;
} // namespace Termutils

template <>
Termutils::terminal_output &Termutils::terminal_output::operator<<(ksdk::string_view s);
template <>
inline Termutils::terminal_output &Termutils::terminal_output::operator<<(Termutils::endl_t)
{
	Termutils::putchar('\n');
	return *this;
}
template <>
inline Termutils::terminal_output &Termutils::terminal_output::operator<<(bool b)
{
	static const char *true_str = "true";
	static const char *false_str = "false";
	(*this) << (b ? ksdk::string_view((char *)true_str, 4) : ksdk::string_view((char *)false_str, 5));
	return *this;
}
template <>
inline Termutils::terminal_output &Termutils::terminal_output::operator<<(const char *v)
{
	Termutils::write(v, strlen(v));
	return *this;
}
template <>
inline Termutils::terminal_output &Termutils::terminal_output::operator<<(Termutils::terminal_output::int_mode n)
{
	this->mode = n;
	return *this;
}
template <>
inline Termutils::terminal_output &Termutils::terminal_output::operator<<(VGA::color_mode n)
{
	VGA::text_color = n;
	return *this;
}