#ifndef OMICRON_COMPONENT_LIGHT_LIGHT_HPP_
#   define OMICRON_COMPONENT_LIGHT_LIGHT_HPP_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include "lib/glm/glm.hpp"

#include "src/omicron/component/Component.hpp"
#include "src/omicron/component/Transform.hpp"

namespace omi {

namespace light {

//! the different possible types of lights
enum Type {
    DIRECTIONAL = 0,
    POINT       = 1,
    SPOT        = 2
};

} // namespace light

/**********************************************************\
| Base class that represents a component that casts light. |
\**********************************************************/
class Light : public Component {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Super constructor for lights
    @param id the identifier of the component
    @param transform the transform to use for the light
    @param power the power of the light
    @param colour the colour of the light */
    Light(
            const std::string&    id,
                  omi::Transform* transform,
                  float           power,
            const glm::vec3&      colour );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    //---------------------------------GETTERS----------------------------------

    /** #Override */
    virtual component::Type getType() const;

    /** @return the type of light this is */
    virtual light::Type getLightType() const = 0;

    /** @return the value of the light ( colour * power ) */
    glm::vec3 getValue() const;

    /** @return the transform of the light */
    omi::Transform* getTransform();

    /** @return the power of the light */
    float getPower() const;

    /** @return the colour of the light */
    const glm::vec3& getColour() const;

    /** @return if this light casts shadows */
    const bool getCastShadows() const;

    /** @return if this light is inversed or not */
    const bool isInversed() const;

    //---------------------------------SETTERS----------------------------------

    /** @param transform the new transform of the light */
    void setTransform( omi::Transform* transform );

    /** @param power the new power of the light */
    void setPower( float power );

    /** @param colour the new colour of the light */
    void setColour( const glm::vec3& colour );

    /** @param castShadows whether or not this light casts shadows */
    void setCastShadow( bool castShadows );

    /** Sets whether this light is inversed or not */
    void setInverse( bool inverse );

protected:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the position of the light
    omi::Transform* m_transform;
    // the power of the light
    float m_power;
    // the colour of the light
    glm::vec3 m_colour;
    // whether this light casts shadows or not
    bool m_castShadows;
    // whether this light is inversed or not
    bool m_inverse;
};

} // namespace omi

#endif
