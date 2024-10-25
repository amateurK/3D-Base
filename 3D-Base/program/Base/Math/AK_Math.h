#pragma once
#include "Point.h"
#include "Line.h"
#include "Segment.h"
#include "Capsule.h"

// 数学的な関数をまとめておく場所
// インスタンスを生成することはない
class AK_Math
{
public:
	// 点に一番近い線分上の点
	static Point<float> CalcPointSegmentPos2D(const Point<float>& p, const Segment<float>& seg);
	static Point<double> CalcPointSegmentPos2D(const Point<double>& p, const Segment<double>& seg);

	// 点と線分の最短距離
	// 第3引数のポインタに点に近い線分の座標を渡す
	static float CalcPointSegmentDistSq2D(const Point<float>& p, const Segment<float>& seg, Point<float>* const outPos = nullptr);
	static double CalcPointSegmentDistSq2D(const Point<double>& p, const Segment<double>& seg);

	// 線分と線分の衝突判定
	// 第3引数のポインタに交点の座標を渡す
	static bool CalcSegmentSegmentCollide2D(const Segment<float>& seg1, const Segment<float>& seg2, Point<float>* const outPos = nullptr);

	// 線分と線分の最短距離
	static float CalcSegmentSegmentDistSq2D(const Segment<float>& seg1, const Segment<float>& seg2);
	static float CalcSegmentSegmentDistSqPos2D(const Segment<float>& seg1, const Segment<float>& seg2, Point<float>* const outPos1, Point<float>* const outPos2);

	// カプセルとカプセルの衝突
	static bool CalcCapsuleCapsuleCollide2D(const Capsule<float>& cap1, const Capsule<float>& cap2);
	static bool CalcCapsuleCapsulePos2D(const Capsule<float>& cap1, const Capsule<float>& cap2, Point<float>* const outPos, float* AofE);

};