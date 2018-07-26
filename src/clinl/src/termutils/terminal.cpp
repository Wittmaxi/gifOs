#include "termutils/terminal.h"

size_t Termutils::tab_size;
Termutils::terminal_output Termutils::cout;
Termutils::endl_t Termutils::endl;

void Termutils::initialize()
{
	tab_size = 4;
	cout.mode = Termutils::terminal_output::int_mode::dec;
}

template <>
Termutils::terminal_output &Termutils::terminal_output::operator<<(ksdk::string_view s)
{
	Termutils::write(s.begin(), s.size());
	return *this;
}