#pragma once
class Vector2
{
public:

	int x;
	int y;

	// コンストラクタ
	Vector2(void);

	// コンストラクタ
	Vector2(int vX, int vY);

	// デストラクタ
	~Vector2(void);

	Vector2 operator+(const Vector2& v) const;
	Vector2 operator-(const Vector2& v) const;
	Vector2 operator*(const float& r) const;
	Vector2 operator/(const float& r) const;

	void operator+=(const Vector2& v);
	void operator-=(const Vector2& v);
	void operator*=(const float& r);
	void operator/=(const float& r);
};

