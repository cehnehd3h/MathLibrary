#include "MathUtility.h"

namespace math
{
    bool CompareFloats(const float val1, const float val2)
    {
        return !(fabs(val1 - val2) > EPSILON);
    }
}