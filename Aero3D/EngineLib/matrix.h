#pragma once

#ifndef matrixH
#define matrixH

#include <math.h>
#include "macros.h"
#include "vector.h"

namespace EngineGL
{
	namespace MathGL
	{

class DLLExport Matrix2
{
public:
        Vector2 v[2];
        Matrix2();
        Matrix2(Vector2 v1, Vector2 v2);
        Matrix2(double n11, double n12, double n21, double n22);
        Matrix2(Matrix2 &m);
        virtual ~Matrix2();

        Matrix2& operator=(double m);
        Matrix2& operator=(const Matrix2& m);

        Matrix2& operator++(int);
        Matrix2& operator--(int);

        Matrix2 operator+(Matrix2& m);
        Matrix2 operator-(Matrix2& m);
        Matrix2 operator*(Matrix2& m);
        Matrix2 operator/(Matrix2& m);
        Matrix2 operator+(double m);
        Matrix2 operator-(double m);
        Matrix2 operator*(double m);
        Matrix2 operator/(double m);
        Vector2 operator*(Vector2 &v);

        Matrix2& operator+=(Matrix2& m);
        Matrix2& operator-=(Matrix2& m);
        Matrix2& operator*=(Matrix2& m);
        Matrix2& operator/=(Matrix2& m);
        Matrix2& operator+=(double m);
        Matrix2& operator-=(double m);
        Matrix2& operator*=(double m);
        Matrix2& operator/=(double m);

        bool operator==(Matrix2& m);
        bool operator!=(Matrix2& m);

        double getDeterminant();
        void  setIdentity();
        void  setTransposition();
        void  setCell(int row, int col, double value);
        bool  IsIdentity();
};

//------------------------------------------------------------------------------
class DLLExport Matrix3
{
public:
        Vector3 v[3];
        Matrix3();
        Matrix3(Vector3 v[3]);
        Matrix3(Vector3 v1, Vector3 v2, Vector3 v3);
        Matrix3(Matrix3 &m);
        virtual ~Matrix3();

        Matrix3& operator=(double m);
        Matrix3& operator=(Matrix3& m);

        Matrix3& operator++(int);
        Matrix3& operator--(int);

        Matrix3 operator+(Matrix3& m);
        Matrix3 operator-(Matrix3& m);
        Matrix3 operator*(Matrix3& m);
        Matrix3 operator/(Matrix3& m);
        Matrix3 operator+(double m);
        Matrix3 operator-(double m);
        Matrix3 operator*(double m);
        Matrix3 operator/(double m);
        Vector3 operator*(Vector3 &v);

        Matrix3& operator+=(Matrix3& m);
        Matrix3& operator-=(Matrix3& m);
        Matrix3& operator*=(Matrix3& m);
        Matrix3& operator/=(Matrix3& m);
        Matrix3& operator+=(double m);
        Matrix3& operator-=(double m);
        Matrix3& operator*=(double m);
        Matrix3& operator/=(double m);

        bool operator==(Matrix3& m);
        bool operator!=(Matrix3& m);

        Matrix2 getMinor(int i, int j);
        double getDeterminant();
        double getDeterminant(int i);
        void  setIdentity();
        void  setTransposition();
        void  setCell(int row, int col, double value);
        bool  IsIdentity();
        static Matrix3 getTranslate(double x, double y, double z);
        static Matrix3 getRotate(double degree, int type);
        static Matrix3 getScale(int type);
};

//------------------------------------------------------------------------------
class DLLExport Matrix4
{
public:
        Vector4 v[4];
        Matrix4();
        Matrix4(Vector4 v[4]);
        Matrix4(Vector4 v1, Vector4 v2, Vector4 v3, Vector4 v4);
        Matrix4(Matrix4 &m);
        virtual ~Matrix4();

        operator double*();

        Matrix4& operator=(double m);
        Matrix4& operator=(const Matrix4& m);

        Matrix4& operator++(int);
        Matrix4& operator--(int);

        Matrix4 operator+(Matrix4& m);
        Matrix4 operator-(Matrix4& m);
        Matrix4 operator*(Matrix4& m);
        Matrix4 operator/(Matrix4& m);
        Matrix4 operator+(double m);
        Matrix4 operator-(double m);
        Matrix4 operator*(double m);
        Matrix4 operator/(double m);
        Vector4 operator*(Vector4 &vector);

        Matrix4& operator+=(Matrix4& m);
        Matrix4& operator-=(Matrix4& m);
        Matrix4& operator*=(Matrix4& m);
        Matrix4& operator/=(Matrix4& m);
        Matrix4& operator+=(double m);
        Matrix4& operator-=(double m);
        Matrix4& operator*=(double m);
        Matrix4& operator/=(double m);

        bool operator==(Matrix4& m);
        bool operator!=(Matrix4& m);

        Matrix3 getMinor(int i, int j);
        double getDeterminant();
        double getDeterminant(int i);
        double getCell(int row, int col);
        
        void  setIdentity();
        void  setTransposition();
        void  setCell(int row, int col, double value);
        bool  IsIdentity();
};
};
};
#endif
