#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 三次元空間にある物体を定義する
// primitiveクラスがあるわけではないので注意
// 
// 製作者	: amateurK
// 作成日	: 2024/12/30
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace AK_Math {

	/// @brief 浮動小数点による誤差の許容値
	constexpr auto EPSILON = 0.000001f;

	// XMVECTORの演算子を追加

	inline DirectX::XMVECTOR operator+(const DirectX::XMVECTOR& left, const DirectX::XMVECTOR& right) {
		return DirectX::XMVectorAdd(left, right);
	}
	inline DirectX::XMVECTOR operator-(const DirectX::XMVECTOR& left, const DirectX::XMVECTOR& right) {
		return DirectX::XMVectorSubtract(left, right);
	}
	inline DirectX::XMVECTOR operator*(const DirectX::XMVECTOR& vec, float scalar) {
		return DirectX::XMVectorScale(vec, scalar);
	}

	/// @brief 三次元空間上の直線
	/// @details 直線状の点一つと方向ベクトル
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

		/// @brief 線上の座標を取得
		/// @param f ベクトルに掛け算する係数
		/// @return 線上の頂点の座標
		inline DirectX::XMVECTOR GetPoint(float f) const {
			return point + vec * f;
		}
	};

	/// @brief 三次元空間上の線分
	/// @details 直線状の点一つと方向ベクトル
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

	/// @brief 三次元空間上の平面
	/// @details 平面上の点一つと法線ベクトル
	struct Plane3 : public Line3 {
		Plane3()
			: Line3() {};
		Plane3(const DirectX::XMVECTOR& p, const DirectX::XMVECTOR& v)
			: Line3(p, v) {};
		Plane3(const Plane3& plane)
			: Line3(plane) {}
		~Plane3() = default;
	};

	/// @brief 三次元空間上の球体
	/// @details 中心の点と半径
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

	/// @brief 三次元空間のカプセル
	/// @details 線分上を半径rの球体がスィープした形
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


