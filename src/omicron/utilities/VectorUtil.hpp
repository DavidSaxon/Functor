#ifndef OMICRON_UTILITIES_VECTORUTIL_HPP_
#   define OMICRON_UTILITIES_VECTORUTIL_HPP_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include "lib/glm/glm.hpp"
#include "lib/Utilitron/MathUtil.hpp"

namespace omi {

namespace vecutil {

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/**Calculates the angle between two glm 2d vectors
@param a the first vector
@param b the second vector
@return the angle between the two vectors */
inline float angleBetween( const glm::vec2& a, const glm::vec2& b )
{
    float angle = ( -1.0f * atan2( a.y - b.y, a.x - b.x ) ) *
            util::math::RADIANS_TO_DEGREES;
    if ( angle < 0.0f )
    {
        angle += 360.0f;
    }
    else if ( angle >= 360.0f )
    {
        angle -= 360.0f;
    }
    return 360.0f - angle;
}

} // namespace vecutil

} // namespace omi

#endif
