#include <iostream>
#include "Vector4.h"

#define UNIT_TEST(statement, result)\
if((statement) != (result))\
{\
std::cout << "'" << #statement << "' FAILED: " << __LINE__ << std::endl;\
}

void TestVectors()
{
    using namespace math;
    Vector4 vec1, vec2;
    float f;

    // equal
    UNIT_TEST(Vector4(-1, 2, -3, 4) == Vector4(-1, 2, -3, 4), true);
    UNIT_TEST(Vector4( ) == Vector4( ), true);

    // not equal
    UNIT_TEST(Vector4(1, 2, 3, 4) != Vector4(0, 0, 0, 0), true);
    UNIT_TEST(Vector4(0, 0, 0, 0) != Vector4(EPSILON + EPSILON, 0, 0, 0), true);

    // length
    UNIT_TEST(Vector4(6, 0, 0, 0).Length( ), 6);
    UNIT_TEST(Vector4(-7, 0, 0, 0).Length( ), 7);
    UNIT_TEST(Vector4(0, 0, 0, 0).Length( ), 0);

    // static length
    UNIT_TEST(Vector4::Length(Vector4(3, 0, 0, 0)), 3);
    UNIT_TEST(Vector4::Length(Vector4(-4, 0, 0, 0)), 4);
    UNIT_TEST(Vector4::Length(Vector4(0, 0, 0, 0)), 0);

    // sqrd length
    UNIT_TEST(Vector4(6, 0, 0, 0).SqrdLength( ), 36);
    UNIT_TEST(Vector4(-7, 0, 0, 0).SqrdLength( ), 49);
    UNIT_TEST(Vector4(0, 0, 0, 0).SqrdLength( ), 0);

    // static sqrd length
    UNIT_TEST(Vector4::SqrdLength(Vector4(3, 0, 0, 0)), 9);
    UNIT_TEST(Vector4::SqrdLength(Vector4(-4, 0, 0, 0)), 16);
    UNIT_TEST(Vector4::SqrdLength(Vector4(0, 0, 0, 0)), 0);

    // normalization
    vec1 = Vector4(3, 0, 0, 0);
    vec1.Normalize( );
    UNIT_TEST(vec1, Vector4(1, 0, 0, 0));

    vec1 = Vector4(-1, 0, 0, 0);
    vec1.Normalize( );
    UNIT_TEST(vec1, Vector4(-1, 0, 0, 0));

    vec1 = Vector4(5, 5, 0, 0);
    vec1.Normalize( );
    UNIT_TEST(vec1, Vector4(0.707106781186f, 0.707106781186f, 0, 0));

    // static normalization
    vec1 = Vector4(3, 0, 0, 0);
    Vector4::Normalize(vec1);
    UNIT_TEST(vec1, Vector4(1, 0, 0, 0));

    vec1 = Vector4(-1, 0, 0, 0);
    Vector4::Normalize(vec1);
    UNIT_TEST(vec1, Vector4(-1, 0, 0, 0));

    vec1 = Vector4(5, 5, 0, 0);
    Vector4::Normalize(vec1);
    UNIT_TEST(vec1, Vector4(0.707106781186f, 0.707106781186f, 0, 0));

    // normalization, catch length
    vec1 = Vector4(3, 0, 0, 0);
    vec1.Normalize(f);
    UNIT_TEST(vec1, Vector4(1, 0, 0, 0));
    UNIT_TEST(f, 3.f);

    vec1 = Vector4(-1, 0, 0, 0);
    vec1.Normalize(f);
    UNIT_TEST(vec1, Vector4(-1, 0, 0, 0));
    UNIT_TEST(f, 1.f);

    vec1 = Vector4(5, 5, 0, 0);
    vec1.Normalize(f);
    UNIT_TEST(vec1, Vector4(0.707106781186f, 0.707106781186f, 0, 0));
    UNIT_TEST(f, 7.07106781186f);

    // static normalization, catch length
    vec1 = Vector4(3, 0, 0, 0);
    Vector4::Normalize(vec1, f);
    UNIT_TEST(vec1, Vector4(1, 0, 0, 0));
    UNIT_TEST(f, 3.f);

    vec1 = Vector4(-1, 0, 0, 0);
    Vector4::Normalize(vec1, f);
    UNIT_TEST(vec1, Vector4(-1, 0, 0, 0));
    UNIT_TEST(f, 1.f);

    vec1 = Vector4(5, 5, 0, 0);
    Vector4::Normalize(vec1, f);
    UNIT_TEST(vec1, Vector4(0.707106781186f, 0.707106781186f, 0, 0));
    UNIT_TEST(f, 7.07106781186f);

    // dot
    // static dot

    // assignment

    // addition
    // subtraction
    // multiplication
    // division

    // add assign
    // subtract assign
    // multiply assign
    // divide assign
}

int main(void)
{
    for (int x = 0; x < 100000; ++x)
        TestVectors( );

    return 0;
}