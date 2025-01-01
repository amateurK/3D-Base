
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �Փ˔���̌v�Z���s��
// 
// �����	: amateurK
// �쐬��	: 2024/12/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "AK_Math.h"

using namespace DirectX;

namespace AK_Math {
	//---------------------------------------------------------------------------------------------
	bool IsCollide(const Line3& line, const DirectX::XMVECTOR& point)
	{
		// ������̓_���画�肵�����_�ւ̃x�N�g���������ƕ��s�Ȃ�Փ˂��Ă���
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
		// �� : t = Dot(Norm(Lv),v) / length(Lv)
		auto t = XMVector3Dot(line.vec, v).m128_f32[0] / XMVector3LengthSq(line.vec).m128_f32[0];
		return line.vec * t - v;
	}

	//---------------------------------------------------------------------------------------------
	DirectX::XMVECTOR GetShortestPath(const Segment3& seg, const DirectX::XMVECTOR& point)
	{
		auto v = point - seg.point;
		// �� : t = Dot(Norm(Lv),v) / length(Lv)
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
		// �e�����̏�̔C�ӂ̓_�����񂾃x�N�g��
		auto v = line1.point - line2.point;
		auto n1 = XMVector3Cross(line1.vec, line2.vec);
		auto n2 = XMVector3Cross(line1.vec, v);

		if (XMVector3LengthSq(n2).m128_f32[0] <= EPSILON) {
			// �I�񂾓_��2������̓_�̏ꍇ�A�_�ƒ����̏Փ˂Ɠ��������ŏՓ˂��Ă���
			return true;
		}
		else if(XMVector3LengthSq(n1).m128_f32[0] > EPSILON
			&& XMVector3LengthSq(XMVector3Cross(n1, n2)).m128_f32[0] < EPSILON) {
			// n1���[���x�N�g���Ȃ�2���������s
			// ��̖@�������s�Ȃ�񒼐��͓����ʏ�ɂ���
			return true;
		}
		return false;
	}

	//---------------------------------------------------------------------------------------------
	bool IsCollide(const Line3& line, const Plane3& plane)
	{
		// �����ƕ��ʂ̖@���������łȂ��Ȃ�Փ˂��Ă���
		if (XMVector3Dot(line.vec, plane.vec).m128_f32[0] <= EPSILON) {
			// �����̏ꍇ

			auto v = line.vec - plane.vec;
			// ���������ʏ�ɏ�ɂ��邩���`�F�b�N
			if (XMVector3Dot(v, plane.vec).m128_f32[0] <= EPSILON) {
				// ���ʏ�ɂ���
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
		// �����̗��[�����ʂ̕\���Ɨ����ɂ���ꍇ�A�����͕��ʂ��ђʂ��Ă���
		// �\�������͕��ʂ̖@���x�N�g���Ƃ̓��ς̐����Ŕ��ʂ���
		auto v1 = plane.point - seg.point;
		auto v2 = plane.point - seg.GetEndPoint();
		return XMVector3Dot(v1, plane.vec).m128_f32[0] *
			XMVector3Dot(v2, plane.vec).m128_f32[0] <= 0;
	}
}