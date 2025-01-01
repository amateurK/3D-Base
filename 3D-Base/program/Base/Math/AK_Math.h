#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Õ“Ë”»’è‚ÌŒvZ‚ğs‚¤
// 
// »ìÒ	: amateurK
// ì¬“ú	: 2024/12/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Primitive.h"

namespace AK_Math {
	// ’¼ü‚Æ“_
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

	// ’¼ü‚Æ’¼ü
	bool IsCollide(const Line3& line1, const Line3& line2);

	// ’¼ü‚Æ•½–Ê
	bool IsCollide(const Line3& line, const Plane3& plane);
	bool IsCollide(const Segment3& seg, const Plane3& plane);
	inline bool IsCollide(const Plane3& plane, const Line3& line) { return IsCollide(line, plane); }
	inline bool IsCollide(const Plane3& plane, const Segment3& seg) { return IsCollide(seg, plane); }


}
