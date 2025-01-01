
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 衝突判定の計算を行う
// 
// 製作者	: amateurK
// 作成日	: 2024/12/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "AK_Math.h"

using namespace DirectX;

namespace AK_Math {
	//---------------------------------------------------------------------------------------------
	bool IsCollide(const Line3& line, const DirectX::XMVECTOR& point)
	{
		// 直線上の点から判定したい点へのベクトルが直線と平行なら衝突している
		auto v = point - line.point;
		return XMVector3LengthSq(XMVector3Cross(v, line.vec)).m128_f32[0] <= EPSILON;
	}

	//---------------------------------------------------------------------------------------------
	bool IsCollide(const Segment3& seg, const DirectX::XMVECTOR& point)
	{
		auto v = point - seg.point;
		return XMVector3LengthSq(XMVector3Cross(v, seg.vec)).m128_f32[0] <= EPSILON
			&& XMVector3LengthSq(v).m128_f32[0] <= XMVector3LengthSq(seg.vec).m128_f32[0];
	}

	//---------------------------------------------------------------------------------------------
	DirectX::XMVECTOR GetShortestPath(const Line3& line, const DirectX::XMVECTOR& point)
	{
		auto v = point - line.point;
		// 式 : t = Dot(Norm(Lv),v) / length(Lv)
		auto t = XMVector3Dot(line.vec, v).m128_f32[0] / XMVector3LengthSq(line.vec).m128_f32[0];
		return line.vec * t - v;
	}

	//---------------------------------------------------------------------------------------------
	DirectX::XMVECTOR GetShortestPath(const Segment3& seg, const DirectX::XMVECTOR& point)
	{
		auto v = point - seg.point;
		// 式 : t = Dot(Norm(Lv),v) / length(Lv)
		auto t = XMVector3Dot(seg.vec, v).m128_f32[0] / XMVector3LengthSq(seg.vec).m128_f32[0];
		if (t <= 0.0f) {
			return v * -1;
		}
		else if(t >= 1.0f) {
			return seg.vec - v;
		}
		else {
			return seg.vec * t - v;
		}
	}

	//---------------------------------------------------------------------------------------------
	float CalcDistanceSq(const Line3& line, const DirectX::XMVECTOR& point)
	{
		return XMVector3LengthSq(GetShortestPath(line, point)).m128_f32[0];
	}

	//---------------------------------------------------------------------------------------------
	float CalcDistanceSq(const Segment3& seg, const DirectX::XMVECTOR& point)
	{
		return XMVector3LengthSq(GetShortestPath(seg, point)).m128_f32[0];
	}

	//---------------------------------------------------------------------------------------------
	float CalcDistance(const Line3& line, const DirectX::XMVECTOR& point)
	{
		return XMVector3Length(GetShortestPath(line, point)).m128_f32[0];
	}

	//---------------------------------------------------------------------------------------------
	float CalcDistance(const Segment3& seg, const DirectX::XMVECTOR& point)
	{
		return XMVector3Length(GetShortestPath(seg, point)).m128_f32[0];
	}

	//---------------------------------------------------------------------------------------------
	bool IsCollide(const Line3& line1, const Line3& line2)
	{
		// 各直線の上の任意の点を結んだベクトル
		auto v = line1.point - line2.point;
		auto n1 = XMVector3Cross(line1.vec, line2.vec);
		auto n2 = XMVector3Cross(line1.vec, v);

		if (XMVector3LengthSq(n2).m128_f32[0] <= EPSILON) {
			// 選んだ点が2直線上の点の場合、点と直線の衝突と同じ原理で衝突している
			return true;
		}
		else if(XMVector3LengthSq(n1).m128_f32[0] > EPSILON
			&& XMVector3LengthSq(XMVector3Cross(n1, n2)).m128_f32[0] < EPSILON) {
			// n1がゼロベクトルなら2直線が平行
			// 二つの法線が平行なら二直線は同平面上にある
			return true;
		}
		return false;
	}

	//---------------------------------------------------------------------------------------------
	bool IsCollide(const Line3& line, const Plane3& plane)
	{
		// 直線と平面の法線が垂直でないなら衝突している
		if (XMVector3Dot(line.vec, plane.vec).m128_f32[0] <= EPSILON) {
			// 垂直の場合

			auto v = line.vec - plane.vec;
			// 直線が平面上に上にあるかをチェック
			if (XMVector3Dot(v, plane.vec).m128_f32[0] <= EPSILON) {
				// 平面上にある
				return true;
			}
			else {
				return false;
			}
		}
		return true;
	}

	//---------------------------------------------------------------------------------------------
	bool IsCollide(const Segment3& seg, const Plane3& plane)
	{
		// 線分の両端が平面の表側と裏側にある場合、線分は平面を貫通している
		// 表か裏かは平面の法線ベクトルとの内積の正負で判別する
		auto v1 = plane.point - seg.point;
		auto v2 = plane.point - seg.GetEndPoint();
		return XMVector3Dot(v1, plane.vec).m128_f32[0] *
			XMVector3Dot(v2, plane.vec).m128_f32[0] <= 0;
	}
}