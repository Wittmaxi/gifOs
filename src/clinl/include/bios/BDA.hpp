#pragma once
#include <stdint.h>
#include <stddef.h>

namespace BIOS
{
	typedef uint16_t IO_COM_port;
	typedef uint16_t IO_LPT_port;
	struct kb_buffer{
		uint8_t data[32];
	};

	struct BDA_t{
	public:
		IO_COM_port& get_com_port(const int idx) const
		{
			return ((IO_COM_port*)0x0400)[idx];
		}
		IO_LPT_port& get_lpt_port(const int idx) const
		{
			return ((IO_LPT_port*)0x0408)[idx];
		}
		intptr_t get_ebda_address() const
		{
			intptr_t v = (*((uint16_t*)0x040E));
			return v<<4;
		}
		uint16_t& get_hw_flags() const
		{
			return *((uint16_t*)0x0410);
		}
		uint16_t& get_kb_state_flags() const
		{
			return *((uint16_t*)0x0417);
		}
		kb_buffer& get_kb_buffer() const
		{
			return *((kb_buffer*)0x041E);
		}
		uint8_t& get_display_mode() const
		{
			return *((uint8_t*)0x0449);
		}
		uint16_t& get_text_mode_cols() const
		{
			return *((uint16_t*)0x044A);
		}
		/*
			Caution, imply an `add` since the BIOS store the number -1
		*/
		uint8_t get_text_mode_rows() const
		{
			return *((uint8_t*)0x0484)+1;
		}
		uint16_t& get_video_byte_size() const
		{
			return *((uint16_t*)0x044C);
		}
		uint16_t& get_base_io_port() const
		{
			return *((uint16_t*)0x0463);
		}
		uint16_t& get_irq0_count() const
		{
			return *((uint16_t*)0x046C);
		}
		uint8_t& get_hdd_count() const
		{
			return *((uint8_t*)0x0475);
		}
		uint16_t& kb_buff_begin() const
		{
			return *((uint16_t*)0x0480);
		}
		uint16_t& kb_buff_end() const
		{
			return *((uint16_t*)0x0482);
		}
		/*
			Bit 7 indicates state of feature connector line 1
 	 		Bit 6 indicates state of feature connector line 0
 	 		Bit 5-4 not used
 	 		Bit 3-0 indicate adapter type switch settings
 	 		0000b = MDA/color 40x25
 	 		0001b = MDA/color 80x25
 	 		0010b = MDA/high-resolution 80x25
 	 		0011b = MDA/high-resolution enhanced
 	 		0100b = CGA 40x25/monochrome
 	 		0101b = CGA 80x25/monochrome
 	 		0110b = color 40x25/MDA
 	 		0111b = color 80x25/MDA
 	 		1000b = high-resolution 80x25/MDA
 	 		1001b = high-resolution enhanced/MDA
 	 		1010b = monochrome/CGA 40x25
 	 		1011b = monochrome/CGA 80x25
			
			(Source: http://www.bioscentral.com/misc/bda.htm)
		*/
		uint8_t& video_adapter_flags() const
		{
			return *((uint8_t*)0x0488);
		}
	};

	const BDA_t BDA= BDA_t();
}