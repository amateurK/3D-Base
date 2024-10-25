#pragma once
#include "Line.h"

// 線分を示す構造体
// vecは距離も示すので、正規化しないように！
// Line<T>を継承するとtemplateが悪さするのでなし
// templateを使用したクラスを継承したとき、親クラスのメンバーを参照するときはthis->をつけなければならない
// https://qiita.com/kaityo256/items/2f24662a9ab8341ad6f4
template<typename T>
struct Segment : public Line<T>
{
	Point<T> pos;
	Point<T> vec;

	Segment() {};
	Segment(const Point<T>& position, const Point<T>& vector)
	{
		pos = position;
		vec = vector;
	};
	~Segment() {};

	// 直線上の点を取得
	Point<T> GetPoint(T t) const {
		return pos + (vec * t);
	}
	// 終点を取得
	Point<T> GetEndPoint() const {
		return pos + vec;
	}
};