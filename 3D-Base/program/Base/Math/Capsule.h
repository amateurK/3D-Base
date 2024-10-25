#pragma once
#include "Segment.h"

template<typename T>
struct Capsule 
{
	Segment<T> seg;	// ’†S‚Ìü•ª
	T r;	// ”¼Œa

	Capsule() {};
	Capsule(const Segment<T>& segment, T radius)
		: seg(segment)
		, r(radius)
	{};
	~Capsule() {};
};