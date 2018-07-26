#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "buffers/vga_buffer.h"
#include "termutils/terminal.h"

extern char bytes[];

void wait(int frames)
{
	for (int j = 0; j < frames; j++)
	{
		for (int i = 0; i < 20000000; i++)
		{
			asm volatile("nop");
		}
	}
}

extern "C"
{
	void kernel_main()
	{
		VGA::initialize();
		Termutils::initialize();

		while (true)
		{
			wait(30);
			Termutils::cout << "h";
		}
	}
}