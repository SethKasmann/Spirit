#ifndef VEC_H
#define VEC_H

#include <iostream>

namespace spirit {

    struct vec2
    {
        vec2();
        vec2(float x_, float y_);
        bool operator==(const vec2& v) const;
        bool operator!=(const vec2& v) const;
        vec2 operator+(const vec2& v) const;
        vec2 operator-(const vec2& v) const;
        vec2 operator*(const vec2& v) const;
        vec2 operator/(const vec2& v) const;
        void operator+=(const vec2& v);
        void operator-=(const vec2& v);
        void operator*=(const vec2& v);
        void operator/=(const vec2& v);
        friend std::ostream& operator<<(std::ostream& o, const vec2& v);
        float x, y;
    };

    struct vec3
    {
        vec3();
        vec3(float x_, float y_, float z_);
        bool operator==(const vec3& v) const;
        bool operator!=(const vec3& v) const;
        vec3 operator+(const vec3& v) const;
        vec3 operator-(const vec3& v) const;
        vec3 operator*(const vec3& v) const;
        vec3 operator/(const vec3& v) const;
        void operator+=(const vec3& v);
        void operator-=(const vec3& v);
        void operator*=(const vec3& v);
        void operator/=(const vec3& v);
        friend std::ostream& operator<<(std::ostream& o, const vec3& v);
        float x, y, z;
    };

    struct vec4
    {
        vec4();
        vec4(float x_, float y_, float z_, float w_);
        bool operator==(const vec4& v) const;
        bool operator!=(const vec4& v) const;
        vec4 operator+(const vec4& v) const;
        vec4 operator-(const vec4& v) const;
        vec4 operator*(const vec4& v) const;
        vec4 operator/(const vec4& v) const;
        void operator+=(const vec4& v);
        void operator-=(const vec4& v);
        void operator*=(const vec4& v);
        void operator/=(const vec4& v);
        friend std::ostream& operator<<(std::ostream& o, const vec4& v);
        float x, y, z, w;
    };


}

#endif