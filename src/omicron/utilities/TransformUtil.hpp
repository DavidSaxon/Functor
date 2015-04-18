#ifndef OMICRON_UTILITES_TRANSFORMUTIL_HPP_
#   define OMICRON_UTILITES_TRANSFORMUTIL_HPP_

#include "src/omicron/Omicron.hpp"

namespace omi {

namespace transutil {

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/** Converts screen space co-ordinates to world space co-ordinates
@param p the screen space co-ordinates to convert
@return the calculated world space co-ordinates */
inline glm::vec3 screenToWorld2D( const glm::vec2& p )
{
    // TODO: take into account camera type

    // get screen size
    glm::vec2 screenSize = displaySettings.getSize();
    // calculate OpenGL world coordinates
    glm::vec2 worldSize(
        static_cast<float>( screenSize.x ) / static_cast<float>( screenSize.y ),
        1.0f
    );
    worldSize.x /= camScale.x;
    worldSize.y /= camScale.y;
    // calculate the world coords
    glm::vec3 worldCoords(
        p.x / screenSize.x,
        p.y / screenSize.y,
        0.0f
    );
    worldCoords.x *= worldSize.x * 2.0f;
    worldCoords.x -= worldSize.x;
    worldCoords.y *= worldSize.y * 2.0f;
    // invert y
    worldCoords.y  = worldSize.y - worldCoords.y;

    return worldCoords;
}

} // namespace transutil

} // namespace omi

#endif
