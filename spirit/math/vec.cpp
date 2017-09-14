#include "vec.h"

#define NDEBUG
#include <cassert>

namespace spirit {

    // Vec2D

    Vec2D::Vec2D()
    {}
    
    Vec2D::Vec2D(float x_, float y_)
    : x(x_), y(y_)
    {}

    bool Vec2D::operator==(const Vec2D& v) const
    {
        return (x == v.x) && (y == v.y);
    }

    bool Vec2D::operator!=(const Vec2D& v) const
    {
        return (x != v.x) || (y != v.y);
    }

    Vec2D Vec2D::operator+(const Vec2D& v) const
    {
        return Vec2D(x + v.x, y + v.y);
    }

    Vec2D Vec2D::operator-(const Vec2D& v) const
    {
        return Vec2D(x - v.x, y - v.y);
    }

    Vec2D Vec2D::operator*(const Vec2D& v) const
    {
        return Vec2D(x * v.x, y * v.y);
    }

    Vec2D Vec2D::operator/(const Vec2D& v) const
    {
        assert(v.x != 0 && v.y != 0);
        return Vec2D(x / v.x, y / v.y);
    }

    void Vec2D::operator+=(const Vec2D& v)
    {
        x += v.x;
        y += v.y;
    }

    void Vec2D::operator-=(const Vec2D& v)
    {
        x -= v.x;
        y -= v.y;
    }

    void Vec2D::operator*=(const Vec2D& v)
    {
        x *= v.x;
        y *= v.y;
    }

    void Vec2D::operator/=(const Vec2D& v)
    {
        assert(v.x != 0 && v.y != 0);
        x /= v.x;
        y /= v.y;
    }

    std::ostream& operator<<(std::ostream& o, const Vec2D& v)
    {
        o << "Vec2D< " << v.x << " " << v.y << " >";
        return o;
    }

    // Vec3D

    Vec3D::Vec3D()
    {}
    
    Vec3D::Vec3D(float x_, float y_, float z_)
    : x(x_), y(y_), z(z_)
    {}

    bool Vec3D::operator==(const Vec3D& v) const
    {
        return (x == v.x) && (y == v.y) && (z == v.z);
    }

    bool Vec3D::operator!=(const Vec3D& v) const
    {
        return (x != v.x) || (y != v.y) || (z != v.z);
    }

    Vec3D Vec3D::operator+(const Vec3D& v) const
    {
        return Vec3D(x + v.x, y + v.y, z + v.z);
    }

    Vec3D Vec3D::operator-(const Vec3D& v) const
    {
        return Vec3D(x - v.x, y - v.y, z - v.z);
    }

    Vec3D Vec3D::operator*(const Vec3D& v) const
    {
        return Vec3D(x * v.x, y * v.y, z * v.z);
    }

    Vec3D Vec3D::operator/(const Vec3D& v) const
    {
        assert(v.x != 0 && v.y != 0 && v.z != 0);
        return Vec3D(x / v.x, y / v.y, z / v.z);
    }

    void Vec3D::operator+=(const Vec3D& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    void Vec3D::operator-=(const Vec3D& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }

    void Vec3D::operator*=(const Vec3D& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
    }

    void Vec3D::operator/=(const Vec3D& v)
    {
        assert(v.x != 0 && v.y != 0 && v.z != 0);
        x /= v.x;
        y /= v.y;
        z /= v.z;
    }

    std::ostream& operator<<(std::ostream& o, const Vec3D& v)
    {
        o << "Vec3D< " << v.x << " " << v.y << " " << v.z << " >";
        return o;
    }

    // Vec4D

    Vec4D::Vec4D()
    {}
    
    Vec4D::Vec4D(float x_, float y_, float z_, float w_)
    : x(x_), y(y_), z(z_), w(w_)
    {}

    bool Vec4D::operator==(const Vec4D& v) const
    {
        return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
    }

    bool Vec4D::operator!=(const Vec4D& v) const
    {
        return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
    }

    Vec4D Vec4D::operator+(const Vec4D& v) const
    {
        return Vec4D(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    Vec4D Vec4D::operator-(const Vec4D& v) const
    {
        return Vec4D(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    Vec4D Vec4D::operator*(const Vec4D& v) const
    {
        return Vec4D(x * v.x, y * v.y, z * v.z, w * v.w);
    }

    Vec4D Vec4D::operator/(const Vec4D& v) const
    {
        assert(v.x != 0 && v.y != 0 && v.z != 0 && v.w != 0);
        return Vec4D(x / v.x, y / v.y, z / v.z, w / v.w);
    }

    void Vec4D::operator+=(const Vec4D& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
    }

    void Vec4D::operator-=(const Vec4D& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
    }

    void Vec4D::operator*=(const Vec4D& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;
    }

    void Vec4D::operator/=(const Vec4D& v)
    {
        assert(v.x != 0 && v.y != 0 && v.z != 0 && v.w != 0);
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;
    }

    std::ostream& operator<<(std::ostream& o, const Vec4D& v)
    {
        o << "Vec4D< " << v.x << " " << v.y << " " << v.z << " " << v.w << " >";
        return o;
    }

}