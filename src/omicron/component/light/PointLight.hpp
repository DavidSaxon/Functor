#ifndef OMICRON_COMPONENT_LIGHT_POINTLIGHT_HPP_
#   define OMICRON_COMPONENT_LIGHT_POINTLIGHT_HPP_

#include "Light.hpp"

namespace omi {

/*********************************************************************\
| Represents a infinitely small point which casts light evenly in all |
| directions.                                                         |
\*********************************************************************/
class PointLight : public Light {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new point light
    @param id the identifier of the component
    @param transform the transform of the light
    @param colour the colour of the light
    @param power the power of the light
    @param constantAtt the constant attenuation value of the light
    @param linearAtt the linear attenuation value of the light
    @param quadraticAtt the quadratic attenuation of the light */
    PointLight(
            const std::string&    id,
                  omi::Transform* transform,
                  float           power,
            const glm::vec3&      colour,
                  float           constantAtt,
                  float           linearAtt,
                  float           quadraticAtt );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    //---------------------------------GETTERS----------------------------------

    /** #Override */
    light::Type getLightType() const;

    /** @return the constant attenuation of the light */
    float getConstantAtt() const;

    /** @return the linear attenuation of the light */
    float getLinearAtt() const;

    /** @return the quadratic attenuation of the light */
    float getQuadraticAtt() const;

    //---------------------------------SETTERS----------------------------------

    /** @param constantAtt the new constant attenuation of the light */
    void setConstantAtt( float constantAtt );

    /** @param linearAtt the new linear attenuation of the light */
    void setLinearAtt( float linearAtt );

    /** @param quadraticAtt the new quadratic attenuation of the light */
    void setQuadraticAtt( float quadraticAtt );

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    float m_constantAtt;
    float m_linearAtt;
    float m_quadraticAtt;
};

} // namespace omi

#endif
