#include "DirectionalLight.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

DirectionalLight::DirectionalLight(
        const std::string&    id,
              omi::Transform* transform,
              float           power,
        const glm::vec3&      colour )
    :
    Light( id, transform, power, colour )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

light::Type DirectionalLight::getLightType() const
{
    return light::DIRECTIONAL;
}

} // namespace omi
