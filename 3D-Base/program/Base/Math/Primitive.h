#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �O������Ԃɂ��镨�̂��`����
// primitive�N���X������킯�ł͂Ȃ��̂Œ���
// 
// �����	: amateurK
// �쐬��	: 2024/12/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace AK_Math {

	/// @brief ���������_�ɂ��덷�̋��e�l
	constexpr auto EPSILON = 0.000001f;

	// XMVECTOR�̉��Z�q��ǉ�

	inline DirectX::XMVECTOR operator+(const DirectX::XMVECTOR& left, const DirectX::XMVECTOR& right) {
		return DirectX::XMVectorAdd(left, right);
	}
	inline DirectX::XMVECTOR operator-(const DirectX::XMVECTOR& left, const DirectX::XMVECTOR& right) {
		return DirectX::XMVectorSubtract(left, right);
	}
	inline DirectX::XMVECTOR operator*(const DirectX::XMVECTOR& vec, float scalar) {
		return DirectX::XMVectorScale(vec, scalar);
	}

	/// @brief �O������ԏ�̒���
	/// @details ������̓_��ƕ����x�N�g��
	struct Line3 {
		DirectX::XMVECTOR point;
		DirectX::XMVECTOR vec;

		Line3() = default;
		Line3(const DirectX::XMVECTOR& p, const DirectX::XMVECTOR& v)
			: point(p)
			, vec(v)
		{}
		Line3(const Line3& line)
			: point(line.point)
			, vec(line.vec)
		{}
		~Line3() = default;

		/// @brief ����̍��W���擾
		/// @param f �x�N�g���Ɋ|���Z����W��
		/// @return ����̒��_�̍��W
		inline DirectX::XMVECTOR GetPoint(float f) const {
			return point + vec * f;
		}
	};

	/// @brief �O������ԏ�̐���
	/// @details ������̓_��ƕ����x�N�g��
	struct Segment3 : public Line3 {
		Segment3()
			: Line3() {};
		Segment3(const DirectX::XMVECTOR& p, const DirectX::XMVECTOR& v)
			: Line3(p, v) {};
		Segment3(const Segment3& seg)
			: Line3(seg) {}
		~Segment3() = default;

		inline DirectX::XMVECTOR GetEndPoint() const {
			return point + vec;
		}
	};

	/// @brief �O������ԏ�̕���
	/// @details ���ʏ�̓_��Ɩ@���x�N�g��
	struct Plane3 : public Line3 {
		Plane3()
			: Line3() {};
		Plane3(const DirectX::XMVECTOR& p, const DirectX::XMVECTOR& v)
			: Line3(p, v) {};
		Plane3(const Plane3& plane)
			: Line3(plane) {}
		~Plane3() = default;
	};

	/// @brief �O������ԏ�̋���
	/// @details ���S�̓_�Ɣ��a
	struct Sphere3 {
		DirectX::XMVECTOR point;
		float radius;
		Sphere3() = default;
		Sphere3(const DirectX::XMVECTOR& p, float r)
			: point(p)
			, radius(r)
		{}
		Sphere3(const Sphere3& sphere)
			: point(sphere.point)
			, radius(sphere.radius)
		{}
		~Sphere3() = default;
	};

	/// @brief �O������Ԃ̃J�v�Z��
	/// @details ������𔼌ar�̋��̂��X�B�[�v�����`
	struct Capsule3 {
		Segment3 seg;
		float radius;
		Capsule3() = default;
		Capsule3(const Segment3& s, float r)
			: seg(s)
			, radius(r)
		{}
		Capsule3(const DirectX::XMVECTOR& begin, const DirectX::XMVECTOR& end, float r)
			: seg(begin, end)
			, radius(r)
		{}
		Capsule3(const Capsule3& capsule)
			: seg(capsule.seg)
			, radius(capsule.radius)
		{}
		~Capsule3() = default;

	};
}


