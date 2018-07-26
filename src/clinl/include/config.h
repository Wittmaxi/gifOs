#pragma once
namespace config
{
	enum class arch{
		ix86
	};

	const bool test_build=true;	
	const arch current_arch=arch::ix86;
}