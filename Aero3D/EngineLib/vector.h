#pragma once

#ifndef vectorH
#define vectorH

#include "macros.h"

namespace EngineGL
{
	namespace MathGL
	{
//------------------------------------------------------------------------------
class DLLExport Vector2
{
public:
        float x,y;

        Vector2();
        Vector2(float x, float y);
        Vector2(const Vector2 &v);
        virtual ~Vector2();

        operator float*();

        Vector2& operator=(float v);
        Vector2& operator=(const Vector2& v);


        Vector2& operator++(int);
        Vector2& operator--(int);

        Vector2 operator+(Vector2& v);
        Vector2 operator-(Vector2& v);
        Vector2 operator+(float v);
        Vector2 operator-(float v);
        Vector2 operator*(float v);
        Vector2 operator/(float v);

        Vector2& operator+=(Vector2& v);
        Vector2& operator-=(Vector2& v);
        Vector2& operator+=(float v);
        Vector2& operator-=(float v);
        Vector2& operator*=(float v);
        Vector2& operator/=(float v);

        bool operator==(Vector2& v);
        bool operator!=(Vector2& v);
};

//------------------------------------------------------------------------------
class DLLExport Vector3
{
public:
        float x,y,z;
        Vector3();
        Vector3(float x, float y, float z);
        Vector3(const Vector3 &v);
        virtual ~Vector3();

        operator float*();

        Vector3& operator=(float v);
        Vector3& operator=(const Vector3& v);


        Vector3& operator++(int);
        Vector3& operator--(int);

        Vector3 operator+(Vector3& v);
        Vector3 operator-(Vector3& v);
        Vector3 operator+(float v);
        Vector3 operator-(float v);
        Vector3 operator*(float v);
        Vector3 operator/(float v);

        Vector3& operator+=(Vector3& v);
        Vector3& operator-=(Vector3& v);
        Vector3& operator+=(float v);
        Vector3& operator-=(float v);
        Vector3& operator*=(float v);
        Vector3& operator/=(float v);

        bool operator==(Vector3& v);
        bool operator!=(Vector3& v);
};

//------------------------------------------------------------------------------
class DLLExport Vector4
{
public:
        float x,y,z,w;
        Vector4();
        Vector4(float x, float y, float z, float w);
        Vector4(const Vector4 &v);
        virtual ~Vector4();

        operator float*();

        Vector4& operator=(float v);
        Vector4& operator=(const Vector4& v);


        Vector4& operator++(int);
        Vector4& operator--(int);

        Vector4 operator+(Vector4& v);
        Vector4 operator-(Vector4& v);
        Vector4 operator+(float v);
        Vector4 operator-(float v);
        Vector4 operator*(float v);
        Vector4 operator/(float v);

        Vector4& operator+=(Vector4& v);
        Vector4& operator-=(Vector4& v);
        Vector4& operator+=(float v);
        Vector4& operator-=(float v);
        Vector4& operator*=(float v);
        Vector4& operator/=(float v);

        bool operator==(Vector4& v);
        bool operator!=(Vector4& v);
};
};
};
//------------------------------------------------------------------------------
#endif
