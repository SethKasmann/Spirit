#include "vec.h"

#define NDEBUG
#include <cassert>

namespace spirit {

    // vec2

    vec2::vec2()
    {}
    
    vec2::vec2(float x_, float y_)
    : x(x_), y(y_)
    {}

    bool vec2::operator==(const vec2& v) const
    {
        return (x == v.x) && (y == v.y);
    }

    bool vec2::operator!=(const vec2& v) const
    {
        return (x != v.x) || (y != v.y);
    }

    vec2 vec2::operator+(const vec2& v) const
    {
        return vec2(x + v.x, y + v.y);
    }

    vec2 vec2::operator-(const vec2& v) const
    {
        return vec2(x - v.x, y - v.y);
    }

    vec2 vec2::operator*(const vec2& v) const
    {
        return vec2(x * v.x, y * v.y);
    }

    vec2 vec2::operator/(const vec2& v) const
    {
        assert(v.x != 0 && v.y != 0);
        return vec2(x / v.x, y / v.y);
    }

    void vec2::operator+=(const vec2& v)
    {
        x += v.x;
        y += v.y;
    }

    void vec2::operator-=(const vec2& v)
    {
        x -= v.x;
        y -= v.y;
    }

    void vec2::operator*=(const vec2& v)
    {
        x *= v.x;
        y *= v.y;
    }

    void vec2::operator/=(const vec2& v)
    {
        assert(v.x != 0 && v.y != 0);
        x /= v.x;
        y /= v.y;
    }

    std::ostream& operator<<(std::ostream& o, const vec2& v)
    {
        o << "vec2< " << v.x << " " << v.y << " >";
        return o;
    }

    // vec3

    vec3::vec3()
    {}
    
    vec3::vec3(float x_, float y_, float z_)
    : x(x_), y(y_), z(z_)
    {}

    bool vec3::operator==(const vec3& v) const
    {
        return (x == v.x) && (y == v.y) && (z == v.z);
    }

    bool vec3::operator!=(const vec3& v) const
    {
        return (x != v.x) || (y != v.y) || (z != v.z);
    }

    vec3 vec3::operator+(const vec3& v) const
    {
        return vec3(x + v.x, y + v.y, z + v.z);
    }

    vec3 vec3::operator-(const vec3& v) const
    {
        return vec3(x - v.x, y - v.y, z - v.z);
    }

    vec3 vec3::operator*(const vec3& v) const
    {
        return vec3(x * v.x, y * v.y, z * v.z);
    }

    vec3 vec3::operator/(const vec3& v) const
    {
        assert(v.x != 0 && v.y != 0 && v.z != 0);
        return vec3(x / v.x, y / v.y, z / v.z);
    }

    void vec3::operator+=(const vec3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    void vec3::operator-=(const vec3& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }

    void vec3::operator*=(const vec3& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
    }

    void vec3::operator/=(const vec3& v)
    {
        assert(v.x != 0 && v.y != 0 && v.z != 0);
        x /= v.x;
        y /= v.y;
        z /= v.z;
    }

    std::ostream& operator<<(std::ostream& o, const vec3& v)
    {
        o << "vec3< " << v.x << " " << v.y << " " << v.z << " >";
        return o;
    }

    // vec4

    vec4::vec4()
    {}
    
    vec4::vec4(float x_, float y_, float z_, float w_)
    : x(x_), y(y_), z(z_), w(w_)
    {}

    bool vec4::operator==(const vec4& v) const
    {
        return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
    }

    bool vec4::operator!=(const vec4& v) const
    {
        return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
    }

    vec4 vec4::operator+(const vec4& v) const
    {
        return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    vec4 vec4::operator-(const vec4& v) const
    {
        return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    vec4 vec4::operator*(const vec4& v) const
    {
        return vec4(x * v.x, y * v.y, z * v.z, w * v.w);
    }

    vec4 vec4::operator/(const vec4& v) const
    {
        assert(v.x != 0 && v.y != 0 && v.z != 0 && v.w != 0);
        return vec4(x / v.x, y / v.y, z / v.z, w / v.w);
    }

    void vec4::operator+=(const vec4& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
    }

    void vec4::operator-=(const vec4& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
    }

    void vec4::operator*=(const vec4& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;
    }

    void vec4::operator/=(const vec4& v)
    {
        assert(v.x != 0 && v.y != 0 && v.z != 0 && v.w != 0);
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;
    }

    std::ostream& operator<<(std::ostream& o, const vec4& v)
    {
        o << "vec4< " << v.x << " " << v.y << " " << v.z << " " << v.w << " >";
        return o;
    }

}