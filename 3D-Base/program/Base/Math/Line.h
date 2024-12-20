#pragma once
#include"Point.h"

// 直線を示す構造体
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

	// 直線上の点を取得
	Point<T> GetPoint(T t) const {
		return pos + (vec * t);
	}
};