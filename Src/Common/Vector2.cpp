#include "Vector2.h"

// コンストラクタ
Vector2::Vector2(void)
{
	x = 0;
	y = 0;
}

// コンストラクタ
Vector2::Vector2(int vX, int vY)
{
	x = vX;
	y = vY;
}

Vector2::~Vector2(void)
{
}

Vector2 Vector2::operator+(const Vector2& v) const
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(const float& r) const
{
	return Vector2(x * r,y * r);
}

Vector2 Vector2::operator/(const float& r) const
{
	if (r == 0)
	{
		return Vector2(0, 0);
	}
	else
	{
		return Vector2(x / r, y / r);
	}
}

void Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
}

void Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
}

void Vector2::operator*=(const float& r)
{
	x *= r;
	y *= r;
}

void Vector2::operator/=(const float& r)
{
	if (r == 0)
	{
		x = 0;
		y = 0;
	}
	else
	{
		x /= r;
		y /= r;
	}
}
