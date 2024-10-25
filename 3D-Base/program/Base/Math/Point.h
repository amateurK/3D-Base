#pragma once
constexpr auto EPSILON = 0.000001f;	// 浮動小数点による誤差の許容値

// 2次元空間上にある1つの点の座標を保持
// 座標だけでなく長さやベクトルなどを持っていることもある
template<typename T>
struct Point
{
	// publicにして直接アクセスできるようにしておく（隠すものでもないし）
public:
	T x;	// x座標
	T y;	// y座標

	// デフォルトコンストラクタ
	Point()
		: x(static_cast<T> (0))
		, y(static_cast<T> (0))
	{}
	// コンストラクタ
	Point(const T px, const T py)
		: x(px)
		, y(py)
	{}
	Point(POINT p)
		: x((T)(p.x))
		, y((T)(p.y))
	{}

	// コピーコンストラクタ
	Point(const Point& point)
		: x(point.x)
		, y(point.y)
	{}
	virtual ~Point()
	{}

	// 代入演算子
	Point& operator=(const Point& right)
	{
		if (this != &right) {
			x = right.x;
			y = right.y;
		}
		return *this;
	}

	// 等価演算子
	bool operator==(const Point& right) const
	{
		return this->x == right.x && this->y == right.y;
	}

	// 非等価演算子
	bool operator!=(const Point& right) const
	{
		return this->x != right.x || this->y != right.y;
	}

	// 加算演算子
	Point operator+(const Point& right) const
	{
		return Point<T>(this->x + right.x, this->y + right.y);
	}
	// 加算代入演算子
	Point& operator+=(const Point& right)
	{
		this->x += right.x;
		this->y += right.y;
		return *this;
	}
	// 減算演算子
	Point operator-(const Point& right) const
	{
		return Point<T>(this->x - right.x, this->y - right.y);
	}
	// 減算代入演算子
	Point& operator-=(const Point& right)
	{
		this->x -= right.x;
		this->y -= right.y;
		return *this;
	}
	// 乗算演算子
	Point operator*(const T right) const
	{
		return Point<T>(this->x * right, this->y * right);
	}
	// 乗算代入演算子
	Point& operator*=(const T right)
	{
		this->x *= right;
		this->y *= right;
		return *this;
	}
	// 除算演算子
	Point operator/(const T right) const
	{
		return Point<T>(this->x / right, this->y / right);
	}
	// 除算代入演算子
	Point& operator/=(const T right)
	{
		this->x /= right;
		this->y /= right;
		return *this;
	}
	// 剰余演算子
	Point operator%(const T right) const
	{
		return Point<T>(this->x % right, this->y % right);
	}
	// 剰余代入演算子
	Point& operator%=(const T right)
	{
		this->x %= right;
		this->y %= right;
		return *this;
	}

	// 単項プラス符号
	Point operator+() const
	{
		return Point<T>(this->x, this->y);
	}
	// 単項マイナス符号
	Point operator-() const
	{
		return Point<T>(-(this->x), -(this->y));
	}

	Point Translate(const T x, const T y) const {
		return Point<T>(this->x + x, this->y + y);
	}

	// カーソルの座標を設定
	bool setCursor(HWND* hwnd)
	{
		POINT point;
		if (!GetCursorPos(&point)) {
			MessageBox(nullptr, L"FAILED : GetCursorPos()", L"Error", MB_OK);
			return false;
		}
		if (!ScreenToClient(*hwnd, &point)) {
			MessageBox(nullptr, L"FAILED : ScreenToClient()", L"Error", MB_OK);
			return false;
		}

		x = (T)(point.x);
		y = (T)(point.y);

		return true;
	}

	// 仰角を求める（thisから引数を見たときの角度）
	// atan2をテーブル化して高速化したいなぁ
	T AngleOfElevation(const T x, const T y) const {
		const double px = (double)(x - this->x);
		const double py = (double)(y - this->y);
		return (T)(std::atan2(py, px));
	}
	T AngleOfElevation(const Point& point) const {
		const double px = (double)(point.x - this->x);
		const double py = (double)(point.y - this->y);
		return (T)(std::atan2(py, px));
	}

	// 長さを求める
	T LengthSq(const T x, const T y) const {
		const T px = x - this->x;
		const T py = y - this->y;
		return px * px + py * py;
	}
	T LengthSq(const Point& point) const {
		const T px = point.x - this->x;
		const T py = point.y - this->y;
		return px * px + py * py;
	}
	T Length(const T x, const T y) const {
		return std::sqrt(LengthSq(x, y));
	}
	T Length(const Point& point) const {
		return std::sqrt(LengthSq(point));
	}

	// ベクトル同士の内積
	T Dot(const Point& point) const {
		return this->x * point.x + this->y * point.y;
	}
	// ベクトル同士の外積
	T Cross(const Point& point) const {
		return this->x * point.y - this->y * point.x;
	}

	// ベクトルの正規化
	void Norm() {
		*this /= Length(0, 0);
	}
	Point GetNorm() const {
		return *this / Length(0, 0);
	}

	// 他方ベクトルと垂直関係か？
	bool IsVertical(const Point& point) const {
		return (abs(this->Dot(point)) < EPSILON);
	}
	// 他方ベクトルと平行関係か？
	bool IsParallel(const Point& point) const {
		return (abs(this->Cross(point)) < EPSILON);
	}
	// 他方ベクトルと鋭角関係か？
	bool IsSharpAngle(const Point& point) const {
		return (this->Dot(point) > 0);
	}


};