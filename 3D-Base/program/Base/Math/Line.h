#pragma once
#include"Point.h"

// ’¼ü‚ğ¦‚·\‘¢‘Ì
template<typename T>
struct Line
{
public:
	Point<T> pos;
	Point<T> vec;

	Line() {};
	Line(const Point<T>& position, const Point<T>& vector)
	{
		pos = position;
		vec = vector;
	};
	~Line() {};

	// ’¼üã‚Ì“_‚ğæ“¾
	Point<T> GetPoint(T t) const {
		return pos + (vec * t);
	}
};