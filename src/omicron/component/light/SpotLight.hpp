#ifndef OMICRON_COMPONENT_LIGHT_SPOTLIGHT_HPP_
#   define OMICRON_COMPONENT_LIGHT_SPOTLIGHT_HPP_

#include "Light.hpp"

namespace omi {

/*********************************************************************\
| Represents an infinitely small light that casts light in a specific |
| direction.                                                          |
\*********************************************************************/
class SpotLight : public Light {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new spot light
    @param id the identifier of the component
    @param transform the transform of the light
    @param colour the colour of the light
    @param power the power of the light
    @param constantAtt the constant attenuation value of the light
    @param linearAtt the linear attenuation value of the light
    @param quadraticAtt the quadratic attenuation of the light
    @param outerArc the angle which determines the maximum size of the cone
    @param innerArc the angle which determines the size of the cone at which
           the light is at maximum intensity */
    SpotLight(
        const std::string&    id,
              omi::Transform* transform,
              float           power,
        const glm::vec3&      colour,
              float           constantAtt,
              float           linearAtt,
              float           quadraticAtt,
              float           outerArc,
              float           innerArc );

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

    /** @return the outer arc of the light */
    float getOuterArc() const;

    /** @return the inner arc of the light */
    float getInnerArc() const;

    //---------------------------------SETTERS----------------------------------

    /** @param constantAtt the new constant attenuation of the light */
    void setConstantAtt( float constantAtt );

    /** @param linearAtt the new linear attenuation of the light */
    void setLinearAtt( float linearAtt );

    /** @param quadraticAtt the new quadratic attenuation of the light */
    void setQuadraticAtt( float quadraticAtt );

    /** @param outerArc the new outer arc of the light */
    void setOuterArc( float outerArc );

    /** @param innerArc the new inner arc of the light */
    void setInnerArc( float innerArc );

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    float m_constantAtt;
    float m_linearAtt;
    float m_quadraticAtt;
    float m_outerArc;
    float m_innerArc;
};

} // namespace omi

#endif
