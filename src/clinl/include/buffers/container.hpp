#pragma once
#include <stddef.h>

inline void* operator new(size_t, void* empl)
{
	return empl;
}

namespace __internals{
	/* Enable_if implementation */
	template<bool b, class T = void>
	struct enable_if{};

	template<class T>
	struct enable_if<true,T>{
		typedef T type;
	};

	/* Enable_if helper implementation */
	template<bool b, class T = void>
	using enable_if_t = typename enable_if<b,T>::type;

	/* static_assert implementaion for comparing integers */
	template<bool b, typename t = enable_if_t<b>>
	class check{

	};
}

namespace ksdk{
	class container
	{
	public:
		size_t size();
	};

	template<class T>
	class typed_container : public container
	{

	};
}