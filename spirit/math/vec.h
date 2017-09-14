#ifndef VEC_H
#define VEC_H

#include <iostream>

namespace spirit {

    struct Vec2D
    {
        Vec2D();
        Vec2D(float x_, float y_);
        bool operator==(const Vec2D& v) const;
        bool operator!=(const Vec2D& v) const;
        Vec2D operator+(const Vec2D& v) const;
        Vec2D operator-(const Vec2D& v) const;
        Vec2D operator*(const Vec2D& v) const;
        Vec2D operator/(const Vec2D& v) const;
        void operator+=(const Vec2D& v);
        void operator-=(const Vec2D& v);
        void operator*=(const Vec2D& v);
        void operator/=(const Vec2D& v);
        friend std::ostream& operator<<(std::ostream& o, const Vec2D& v);
        float x, y;
    };

    struct Vec3D
    {
        Vec3D();
        Vec3D(float x_, float y_, float z_);
        bool operator==(const Vec3D& v) const;
        bool operator!=(const Vec3D& v) const;
        Vec3D operator+(const Vec3D& v) const;
        Vec3D operator-(const Vec3D& v) const;
        Vec3D operator*(const Vec3D& v) const;
        Vec3D operator/(const Vec3D& v) const;
        void operator+=(const Vec3D& v);
        void operator-=(const Vec3D& v);
        void operator*=(const Vec3D& v);
        void operator/=(const Vec3D& v);
        friend std::ostream& operator<<(std::ostream& o, const Vec3D& v);
        float x, y, z;
    };

    struct Vec4D
    {
        Vec4D();
        Vec4D(float x_, float y_, float z_, float w_);
        bool operator==(const Vec4D& v) const;
        bool operator!=(const Vec4D& v) const;
        Vec4D operator+(const Vec4D& v) const;
        Vec4D operator-(const Vec4D& v) const;
        Vec4D operator*(const Vec4D& v) const;
        Vec4D operator/(const Vec4D& v) const;
        void operator+=(const Vec4D& v);
        void operator-=(const Vec4D& v);
        void operator*=(const Vec4D& v);
        void operator/=(const Vec4D& v);
        friend std::ostream& operator<<(std::ostream& o, const Vec4D& v);
        float x, y, z, w;
    };


}

#endif