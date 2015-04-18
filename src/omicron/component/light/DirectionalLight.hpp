#ifndef OMICRON_COMPONENT_LIGHT_DIRECTIONALLIGHT_HPP_
#   define OMICRON_COMPONENT_LIGHT_DIRECTIONALLIGHT_HPP_

#include "Light.hpp"

namespace omi {

/*******************************************************************\
| Represents a light with no fall-off which is infinitely far away. |
\*******************************************************************/
class DirectionalLight : public Light {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new directional light
    @param id the identifier of the component
    @param transform the transform to use for the light
    @param power the power of the light
    @param colour the colour of the light */
    DirectionalLight(
            const std::string&    id,
                  omi::Transform* transform,
                  float           power,
            const glm::vec3&      colour );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    light::Type getLightType() const;

};

} // namespace omi

#endif
