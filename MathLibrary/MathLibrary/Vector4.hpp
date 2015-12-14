#pragma once

namespace math
{
#ifdef USE_SIMD
    // constructors /////////////////////////////////////////////////
    inline Vector4::Vector4(const SIMD128& value)
        : m_simd128(value) {}

    inline Vector4::Vector4(void)
        : m_x(0.f)
        , m_y(0.f)
        , m_z(0.f)
        , m_w(0.f) {}

    inline Vector4::Vector4(const Vector4& vec)
        : m_simd128(vec.m_simd128) {}

    inline Vector4::Vector4(
        const float x,
        const float y,
        const float z,
        const float w
        )
        : m_x(x)
        , m_y(y)
        , m_z(z)
        , m_w(w) {}

    // length ///////////////////////////////////////////////////////
    inline float Vector4::Length(void) const
    {
        return Length(*this);
    }

    inline float Vector4::Length(const Vector4& vec)
    {
        return sqrtf(SqrdLength(vec));;
    }

    inline float Vector4::SqrdLength(void) const
    {
        return SqrdLength(*this);
    }

    inline float Vector4::SqrdLength(const Vector4& vec)
    {
        return Dot(vec, vec);
    }

    // normalization ////////////////////////////////////////////////
    inline void Vector4::Normalize(void)
    {
        Normalize(*this);
    }

    inline void Vector4::Normalize(Vector4 &vec)
    {
        vec /= Length(vec);
    }

    inline void Vector4::Normalize(float& length)
    {
        Normalize(*this, length);
    }

    inline void Vector4::Normalize(Vector4 &vec, float &length)
    {
        length = Length(vec);
        vec /= length;
    }

    // dot product //////////////////////////////////////////////////
    inline float Vector4::Dot(const Vector4 &rhs) const
    {
        return Dot(*this, rhs);
    }

    inline float Vector4::Dot(const Vector4 &lhs, const Vector4 &rhs)
    {
        auto vd = _mm_mul_ps(lhs.m_simd128, rhs.m_simd128); // multiply them together, x is stored in element 0
        auto z = _mm_movehl_ps(vd, vd);                     // move element 3 into element 0 of this vector
        auto y = _mm_shuffle_ps(vd, vd, 0x55);              // move element 1 into element 0 for this vector

        // add the first element in vd (x) and the first element of y (y)
        vd = _mm_add_ss(vd, y);

        // add the z to our current sum
        vd = _mm_add_ss(vd, z);

        // return the first element of vd
        return _mm_cvtss_f32(vd);
    }

    inline float Vector4::Distance(const Vector4 &rhs) const
    {
        return Distance(*this, rhs);
    }

    inline float Vector4::Distance(const Vector4 &lhs, const Vector4 &rhs)
    {
        return sqrtf(SqrdDistance(lhs, rhs));
    }

    inline float Vector4::SqrdDistance(const Vector4 &rhs) const
    {
        return SqrdDistance(*this, rhs);
    }

    inline float Vector4::SqrdDistance(const Vector4 &lhs, const Vector4 &rhs)
    {
        Vector4 sub = Vector4(_mm_sub_ps(lhs.m_simd128, rhs.m_simd128));
        return Dot(sub, sub);
    }

    // operators ////////////////////////////////////////////////////
    inline const Vector4 &Vector4::operator=(const Vector4 &rhs)
    {
        m_simd128 = rhs.m_simd128;
        return *this;
    }

    inline Vector4 Vector4::operator+(const Vector4& rhs) const
    {
        return Vector4(_mm_add_ps(m_simd128, rhs.m_simd128));
    }

    inline Vector4 Vector4::operator-(const Vector4& rhs) const
    {
        return Vector4(_mm_sub_ps(m_simd128, rhs.m_simd128));
    }

    inline Vector4 Vector4::operator*(const float &rhs) const
    {
        return Vector4(_mm_mul_ps(m_simd128, _mm_set1_ps(rhs)) );
    }

    inline Vector4 Vector4::operator/(const float &rhs) const
    {
        return Vector4(_mm_div_ps(m_simd128, _mm_set1_ps(rhs)));
    }

    inline const Vector4 &Vector4::operator+=(const Vector4 &rhs)
    {
        m_simd128 = _mm_add_ps(m_simd128, rhs.m_simd128);
        return *this;
    }

    inline const Vector4 &Vector4::operator-=(const Vector4 &rhs)
    {
        m_simd128 = _mm_sub_ps(m_simd128, rhs.m_simd128);
        return *this;
    }
    inline const Vector4 &Vector4::operator*=(const float &rhs)
    {
        m_simd128 = _mm_mul_ps(m_simd128, _mm_set1_ps(rhs));
        return *this;
    }

    inline const Vector4 &Vector4::operator/=(const float &rhs)
    {
        m_simd128 = _mm_div_ps(m_simd128, _mm_set1_ps(rhs));
        return *this;
    }

    inline bool Vector4::operator==(const Vector4& rhs) const
    {
        // compare. 0 means false, else (int)(-1) is high
        auto result = _mm_cmpeq_ps(m_simd128, rhs.m_simd128);

        // create a mask by moving the high bit of each element into temp
        auto temp = _mm_movemask_ps(result);

        // check if all bits are high
        return (temp == 15);
    }

    inline bool Vector4::operator!=(const Vector4& rhs) const
    {
        return !(*this == rhs);
    }

#else
    // constructors /////////////////////////////////////////////////

    inline Vector4::Vector4(void)
        : m_x(0.f)
        , m_y(0.f)
        , m_z(0.f)
        , m_w(0.f) {}

    inline Vector4::Vector4(const Vector4& vec)
        : m_x(vec.m_x)
        , m_y(vec.m_y) 
        , m_z(vec.m_z) 
        , m_w(vec.m_w) {}

    inline Vector4::Vector4(
        const float x,
        const float y,
        const float z,
        const float w
        )
        : m_x(x)
        , m_y(y)
        , m_z(z)
        , m_w(w) {}

    // length ///////////////////////////////////////////////////////
    inline float Vector4::Length(void) const
    {
        return Length(*this);
    }

    inline float Vector4::Length(const Vector4& vec)
    {
        return sqrtf(SqrdLength(vec));
    }

    inline float Vector4::SqrdLength(void) const
    {
        return SqrdLength(*this);
    }

    inline float Vector4::SqrdLength(const Vector4& vec)
    {
        return Dot(vec, vec);
    }

    // normalization ////////////////////////////////////////////////
    inline void Vector4::Normalize(void)
    {
        Normalize(*this);
    }

    inline void Vector4::Normalize(Vector4 &vec)
    {
        vec /= Length(vec);
    }

    inline void Vector4::Normalize(float& length)
    {
        Normalize(*this, length);
    }

    inline void Vector4::Normalize(Vector4 &vec, float &length)
    {
        length = Length(vec);
        vec /= length;
    }

    // dot product //////////////////////////////////////////////////
    inline float Vector4::Dot(const Vector4 &rhs) const
    {
        return Dot(*this, rhs);
    }

    inline float Vector4::Dot(const Vector4 &lhs, const Vector4 &rhs)
    {
        float sum = 0;

        for (int x = 0; x < 4; ++x)
            sum += lhs.m_array[ x ] * rhs.m_array[ x ];

        return sum;
    }

    // operators ////////////////////////////////////////////////////
    inline const Vector4 &Vector4::operator=(const Vector4 &rhs)
    {
        for (int x = 0; x < 4; ++x)
           m_array[ x ] = rhs.m_array[ x ];
        return *this;
    }

    inline Vector4 Vector4::operator+(const Vector4& rhs) const
    {
        Vector4 retVal;
        for (int x = 0; x < 4; ++x)
            retVal.m_array[ x ] = m_array[x] + rhs.m_array[ x ];

        return retVal;
    }

    inline Vector4 Vector4::operator-(const Vector4& rhs) const
    {
        Vector4 retVal;
        for (int x = 0; x < 4; ++x)
            retVal.m_array[ x ] = m_array[ x ] - rhs.m_array[ x ];

        return retVal;
    }

    inline Vector4 Vector4::operator*(const float &rhs) const
    {
        Vector4 retVal;
        for (int x = 0; x < 4; ++x)
            retVal.m_array[ x ] = m_array[ x ] * rhs;

        return retVal;
    }

    inline Vector4 Vector4::operator/(const float &rhs) const
    {
        Vector4 retVal;
        for (int x = 0; x < 4; ++x)
            retVal.m_array[ x ] = m_array[ x ] / rhs;

        return retVal;
    }

    inline const Vector4 &Vector4::operator+=(const Vector4 &rhs)
    {
        for (int x = 0; x < 4; ++x)
            m_array[ x ] += rhs.m_array[ x ];
        return *this;
    }

    inline const Vector4 &Vector4::operator-=(const Vector4 &rhs)
    {
        for (int x = 0; x < 4; ++x)
            m_array[ x ] -= rhs.m_array[ x ];
        return *this;
    }
    inline const Vector4 &Vector4::operator*=(const float &rhs)
    {
        for (int x = 0; x < 4; ++x)
            m_array[ x ] *= rhs;
        return *this;
    }

    inline const Vector4 &Vector4::operator/=(const float &rhs)
    {
        for (int x = 0; x < 4; ++x)
            m_array[ x ] /= rhs;
        return *this;
    }

    inline bool Vector4::operator==(const Vector4& rhs) const
    {
        for (int x = 0; x < 4; ++x)
            if (!CompareFloats(m_array[x], rhs.m_array[x]))
                return false;

        return true;
    }

    inline bool Vector4::operator!=(const Vector4& rhs) const
    {
        return !(*this == rhs);
    }
#endif // USE_SIMD
}