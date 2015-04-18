#include "Transform.hpp"

#include "lib/Utilitron/MathUtil.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

Transform::Transform(
          const std::string           id,
          const glm::vec3&            t,
          const glm::vec3&            r,
          const glm::vec3&            s,
                axis_space::AxisSpace axisSpace ) :
    Component  ( id ),
    parent     ( NULL ),
    translation( t ),
    rotation   ( r ),
    scale      ( s )
{
}

Transform::Transform(
          const std::string           id,
                Transform*            p,
          const glm::vec3&            t,
          const glm::vec3&            r,
          const glm::vec3&            s,
                axis_space::AxisSpace axisSpace ) :
    Component  ( id ),
    parent     ( p ),
    translation( t ),
    rotation   ( r ),
    scale      ( s )
{
}

Transform::Transform( const std::string& id, const Transform& other ) :
    Component  ( id ),
    parent     ( other.parent ),
    translation( other.translation ),
    rotation   ( other.rotation ),
    scale      ( other.scale )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

axis_space::AxisSpace Transform::getAxisSpace() const
{
    return m_axisSpace;
}

glm::vec3 Transform::computeTranslation() const
{
    glm::vec3 computed( 0.0f, 0.0f, 0.0f );
    // compute from parent
    if ( parent != NULL )
    {
        // TODO: axis spaces
        computed = parent->computeTranslation();
    }
    // add this translation
    computed += translation;

    return computed;
}

glm::vec3 Transform::computeRotation() const
{
    glm::vec3 computed( 0.0f, 0.0f, 0.0f );
    // compute from parent
    if ( parent != NULL )
    {
        // TODO: axis spaces
        computed = parent->computeRotation();
    }
    // add this rotation
    computed += rotation;

    return computed;
}

glm::vec3 Transform::computeScale() const
{
    glm::vec3 computed( 1.0f, 1.0f, 1.0f );
    // compute from parent
    if ( parent != NULL )
    {
        // TODO: axis spaces
        computed = parent->computeScale();
    }
    // add this scale
    computed *= scale;

    return computed;
}

void Transform::apply( glm::mat4& matrix )
{
    // apply the parent if there is one
    if ( parent != NULL )
    {
        parent->apply( matrix );
    }

    // translation
    matrix *= glm::translate( translation );

    // rotation
    matrix *= glm::rotate(
            rotation.x * util::math::DEGREES_TO_RADIANS,
            glm::vec3( 1.0f, 0.0f, 0.0f )
    );
    matrix *= glm::rotate(
            rotation.y * util::math::DEGREES_TO_RADIANS,
            glm::vec3( 0.0f, 1.0f, 0.0f )
    );
    matrix *= glm::rotate(
            rotation.z * util::math::DEGREES_TO_RADIANS,
            glm::vec3( 0.0f, 0.0f, 1.0f )
    );

    // scale
    matrix *= glm::scale( scale );
}

void Transform::applyReverse( glm::mat4& matrix )
{
    // scale
    matrix *= glm::scale( scale );

    // rotation
    matrix *= glm::rotate(
            -rotation.x * util::math::DEGREES_TO_RADIANS,
            glm::vec3( 1.0f, 0.0f, 0.0f )
    );
    matrix *= glm::rotate(
            -rotation.y * util::math::DEGREES_TO_RADIANS,
            glm::vec3( 0.0f, 1.0f, 0.0f )
    );
    matrix *= glm::rotate(
            -rotation.z * util::math::DEGREES_TO_RADIANS,
            glm::vec3( 0.0f, 0.0f, 1.0f )
    );

    // translation
    matrix *= glm::translate( -translation );

    // apply the parent if there is one
    if ( parent != NULL )
    {
        parent->applyReverse( matrix );
    }

}

} // namespace omi
