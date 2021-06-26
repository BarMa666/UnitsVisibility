#include "Vector2.h"
#define _USE_MATH_DEFINES 
#include <math.h>

Vector2::Vector2(const CoordT& _x, const CoordT& _y) 
    : m_x(_x)
    , m_y(_y)
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
    return x() * _other.x() + y() * _other.y();
}

Vector2::CoordT Vector2::modulo() const
{
    return sqrtf(x() * x() + y() * y());
}

Vector2::CoordT Vector2::angle(const Vector2& _other) const
{
    return static_cast<float>(_acos(scalar(_other) / (modulo() * _other.modulo())) * (180.0 / M_PI));
}

Vector2 Vector2::operator-(const Vector2& _other) const
{
    return Vector2(x() - _other.x(), y() - _other.y());
}

Vector2 Vector2::operator+(const Vector2& _other) const
{
    return Vector2(x() + _other.x(), y() + _other.y());
}

Vector2::CoordT Vector2::_acos(CoordT _val) const
{
    if (_val <= -1.0) {
        return static_cast<float>(M_PI);
    }
    else if (_val >= 1.0) {
        return 0;
    }
    else {
        return acosf(_val);
    }
}
