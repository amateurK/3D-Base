#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 衝突判定の計算を行う
// 
// 製作者	: amateurK
// 作成日	: 2024/12/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Primitive.h"

namespace AK_Math {
	// 直線と点
	bool IsCollide(const Line3& line, const DirectX::XMVECTOR& point);
	bool IsCollide(const Segment3& seg, const DirectX::XMVECTOR& point);
	inline bool IsCollide(const DirectX::XMVECTOR& point, const Line3& line) { return IsCollide(line, point); }
	inline bool IsCollide(const DirectX::XMVECTOR& point, const Segment3& seg) { return IsCollide(seg, point); }

	DirectX::XMVECTOR GetShortestPath(const Line3& line, const DirectX::XMVECTOR& point);
	DirectX::XMVECTOR GetShortestPath(const Segment3& seg, const DirectX::XMVECTOR& point);
	inline DirectX::XMVECTOR GetShortestPath(const DirectX::XMVECTOR& point, const Line3& line) { return GetShortestPath(line, point); }
	inline DirectX::XMVECTOR GetShortestPath(const DirectX::XMVECTOR& point, const Segment3& seg) { return GetShortestPath(seg, point); }
	
	float CalcDistanceSq(const Line3& line, const DirectX::XMVECTOR& point);
	float CalcDistanceSq(const Segment3& seg, const DirectX::XMVECTOR& point);
	inline float CalcDistanceSq(const DirectX::XMVECTOR& point, const Line3& line) { return CalcDistanceSq(line, point); }
	inline float CalcDistanceSq(const DirectX::XMVECTOR& point, const Segment3& seg) { return CalcDistanceSq(seg, point); }
	float CalcDistance(const Line3& line, const DirectX::XMVECTOR& point);
	float CalcDistance(const Segment3& seg, const DirectX::XMVECTOR& point);
	inline float CalcDistance(const DirectX::XMVECTOR& point, const Line3& line) { return CalcDistanceSq(line, point); }
	inline float CalcDistance(const DirectX::XMVECTOR& point, const Segment3& seg) { return CalcDistanceSq(seg, point); }

	// 直線と直線
	bool IsCollide(const Line3& line1, const Line3& line2);

	// 直線と平面
	bool IsCollide(const Line3& line, const Plane3& plane);
	bool IsCollide(const Segment3& seg, const Plane3& plane);
	inline bool IsCollide(const Plane3& plane, const Line3& line) { return IsCollide(line, plane); }
	inline bool IsCollide(const Plane3& plane, const Segment3& seg) { return IsCollide(seg, plane); }

	// 球体と球体
	bool IsCollide(const Sphere3& sphere1, const Sphere3& sphere2);

}
