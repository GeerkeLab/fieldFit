/**
 * Copyright (c) 2014 Koen Visscher, Paul Visscher and individual contributors.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once
#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include "vec4.h"

class Matrix4
{
    friend Matrix4 operator+( const Matrix4 &m1, const Matrix4 &m2 );
    friend Matrix4 operator-( const Matrix4 &m1, const Matrix4 &m2 );
    friend Matrix4 operator*( const Matrix4 &m1, const Matrix4 &m2 );
    friend Matrix4 operator*( const Matrix4 &m, const F32 s );
    friend Vec4 operator*( const Matrix4 &m, const Vec4 &v );

public:

    Matrix4();

    Matrix4( const F32 a11, const F32 a12, const F32 a13, const F32 a14,
             const F32 a21, const F32 a22, const F32 a23, const F32 a24,
             const F32 a31, const F32 a32, const F32 a33, const F32 a34,
             const F32 a41, const F32 a42, const F32 a43, const F32 a44 );

    Matrix4( const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, const Vec4 &v4 );

    Matrix4( const Matrix4 &other );

    Matrix4 &operator=( const Matrix4 &m );

    Matrix4 &operator*=( const Matrix4 &m );

    Matrix4 &operator+=( const Matrix4 &m );

    Matrix4 &operator-=( const Matrix4 &m );

    bool operator==( const Matrix4 &m ) const;

    bool operator!=( const Matrix4 &m ) const;

    void SetColumn( const U8 column, const Vec4 &v );

    Vec4 GetColumn( const U8 column ) const;

    void SetRow( const U8 row, const Vec4 &v );

    Vec4 GetRow( const U8 row ) const;

    Matrix4 Scale( const Vec4 &v ) const;

    Matrix4 GetTranspose() const;

    Matrix4 GetAbsolute() const;

    Matrix4 GetAdjoint() const;

    Matrix4 GetInverse() const;

    void SetIdentity();

    F32 GetCofactor( const U8 row, const U8 column ) const;

    F32 GetDeterminant() const;

    void SetValue( const F32 a11, const F32 a12, const F32 a13, const F32 a14,
                   const F32 a21, const F32 a22, const F32 a23, const F32 a24,
                   const F32 a31, const F32 a32, const F32 a33, const F32 a34,
                   const F32 a41, const F32 a42, const F32 a43, const F32 a44 );

private:

    Vec4 mValues[4];

    F32 Dotx( const Vec4 &v ) const;

    F32 Doty( const Vec4 &v ) const;

    F32 Dotz( const Vec4 &v ) const;

    F32 Dotw( const Vec4 &v ) const;
};

Matrix4 operator+( const Matrix4 &m1, const Matrix4 &m2 );
Matrix4 operator-( const Matrix4 &m1, const Matrix4 &m2 );
Matrix4 operator*( const Matrix4 &m1, const Matrix4 &m2 );
Matrix4 operator*( const Matrix4 &m, const F32 s );
Vec4 operator*( const Matrix4 &m, const Vec4 &v );

#endif