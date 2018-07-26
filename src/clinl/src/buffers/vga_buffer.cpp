#include "buffers/vga_buffer.h"
#include "bios/BDA.hpp"

ksdk::buffer<char> VGA::buffer;
ksdk::buffer<VGA::character> VGA::text_buffer;

size_t VGA::TEXT_WIDTH;
size_t VGA::TEXT_HEIGHT;
size_t VGA::text_cursor;
VGA::color_mode VGA::text_color;

void VGA::initialize()
{
	TEXT_WIDTH = BIOS::BDA.get_text_mode_cols();
	TEXT_HEIGHT = BIOS::BDA.get_text_mode_rows();
	text_cursor = 0;

	VGA::buffer = ksdk::buffer<char>((char *)0x000A0000, (char *)0x000BFFFF);
	VGA::text_buffer = ksdk::buffer<VGA::character>(
		(VGA::character *)0x000B8000,
		TEXT_WIDTH * TEXT_HEIGHT);

	text_color = make_color_mode(color::WHITE);

	for (VGA::character &c : VGA::text_buffer)
	{
		c = VGA::character(' ', text_color);
	}
}

__internals::check<sizeof(VGA::character) * 8 == 16> a;