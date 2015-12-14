#pragma once

#include "SIMDDefines.h"
#include "MathDefines.h"
#include "MathUtility.h"

namespace math
{
    class Vector4
    {
    public:
        // constructors
        Vector4(void);
        Vector4(const Vector4 &vec);
        Vector4(
            const float x, 
            const float y, 
            const float z, 
            const float w
        );

        // general functions
        float Length(void) const;
        static float Length(const Vector4 &vec);

        float SqrdLength(void) const;
        static float SqrdLength(const Vector4 &vec);
        
        void Normalize(void);
        static void Normalize(Vector4 &vec);

        void Normalize(float &length);
        static void Normalize(Vector4 &vec, float &length);
        

        float Dot(const Vector4 &rhs) const;
        static float Dot(const Vector4 &lhs, const Vector4 &rhs);

        float Distance(const Vector4 &rhs) const;
        static float Distance(const Vector4 &lhs, const Vector4 &rhs);

        float SqrdDistance(const Vector4 &rhs) const;
        static float SqrdDistance(const Vector4 &lhs, const Vector4 &rhs);

        // operators ////////////////////////////////////////////////
        // assignment
        const Vector4 &operator=(const Vector4 &rhs);

        // mathematical
        Vector4 operator+(const Vector4 &rhs) const;
        Vector4 operator-(const Vector4 &rhs) const;
        Vector4 operator*(const float &rhs) const;
        Vector4 operator/(const float &rhs) const;

        const Vector4 &operator+=(const Vector4 &rhs);
        const Vector4 &operator-=(const Vector4 &rhs);
        const Vector4 &operator*=(const float &rhs);
        const Vector4 &operator/=(const float &rhs);

        // comparison
        bool operator==(const Vector4 &rhs) const;
        bool operator!=(const Vector4 &rhs) const;

    private:
#ifdef USE_SIMD
        explicit Vector4(const SIMD128 &value);

        union
        {
            // for SSE
            SIMD128 m_simd128;

            // ease of access
            struct
            {
                float m_x;
                float m_y;
                float m_z;
                float m_w;
            };

            // any iteration we need to do
            float m_array[ 4 ];
        };
#else
        union
        {
            // ease of access
            struct
            {
                float m_x;
                float m_y;
                float m_z;
                float m_w;
            };

            // any iteration we need to do
            float m_array[ 4 ];
        };
#endif
    };
}

#include "Vector4.hpp"