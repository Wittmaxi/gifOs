#pragma once

template<class it_src, class it_dest>
it_dest copy(it_src src_b, it_src src_e,it_dest dest_b)
{
	auto it=src_b;
	auto wit=dest_b;
	for(;it!=src_e;++it,++wit)
		*wit=*it;
	return wit;
}