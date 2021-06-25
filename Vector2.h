#pragma once
#include <utility>

class Vector2
{
public:
	using CoordT = float;

	Vector2(const CoordT& _x, const CoordT& _y);

	CoordT x() const;
	CoordT y() const;

	CoordT scalar(const Vector2& _other) const;
	CoordT modulo() const;

	CoordT angle(const Vector2& _other) const;

	Vector2 operator-(const Vector2& _other) const;
	Vector2 operator+(const Vector2& _other) const;
private:
	CoordT m_x;
	CoordT m_y;
};

