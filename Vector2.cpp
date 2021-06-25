#include "Vector2.h"
#define _USE_MATH_DEFINES 
#include <math.h>

Vector2::Vector2(const CoordT& _x, const CoordT& _y) : m_x(_x), m_y(_y)
{
}

Vector2::CoordT Vector2::x() const
{
    return m_x;
}

Vector2::CoordT Vector2::y() const
{
    return m_y;
}

Vector2::CoordT Vector2::scalar(const Vector2& _other) const
{
    return x() * _other.y() + _other.x() * y();
}

Vector2::CoordT Vector2::modulo() const
{
    return sqrtf(x() * x() + y() * y());
}

Vector2::CoordT Vector2::angle(const Vector2& _other) const
{
    auto temp_scalar = scalar(_other);
    auto modulo_lhs = modulo();
    auto modulo_rhs = _other.modulo();
    auto val = scalar(_other) / (modulo() * _other.modulo());
    auto angle = acosf(scalar(_other) / (modulo() * _other.modulo())) * (180.0 / M_PI);
    auto rad = acosf(scalar(_other) / (modulo() * _other.modulo()));
    return static_cast<float>(acosf(scalar(_other) / (modulo() * _other.modulo())) * (180.0 / M_PI));
}

Vector2 Vector2::operator-(const Vector2& _other) const
{
    auto temp_x = x() - _other.x();
    auto temp_y = y() - _other.y();
    return Vector2(x() - _other.x(), y() - _other.y());
}

Vector2 Vector2::operator+(const Vector2& _other) const
{
    auto temp_x = x() + _other.x();
    auto temp_y = y() + _other.y();
    return Vector2(x() + _other.x(), y() + _other.y());
}
