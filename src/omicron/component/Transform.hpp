#ifndef OMICRON_COMPONENT_TRANSFORM_H_
#   define OMICRON_COMPONENT_TRANSFORM_H_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include "lib/glm/glm.hpp"
#include "lib/glm/gtx/transform.hpp"

#include "src/omicron/component/Component.hpp"

namespace omi {

/**********************************************************************************\
| The types of axis spaces that can be used to compute the effects of a transform. |
\**********************************************************************************/

namespace axis_space {

enum AxisSpace {
    LOCAL,
    PARENT,
    GLOBAL
};

} //namespace axis_space

/***************************************************************************\
| A transform defines the translation, rotation, and position of an entity. |
| There must always be exactly one transform component per entity and is    |
| created by default under the id "transform".                              |
\***************************************************************************/
class Transform : public Component {
private:

    //--------------------------------------------------------------------------
    //                                RESTRICTIONS
    //--------------------------------------------------------------------------

    DISALLOW_DEFAULT_COPY( Transform );

public:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    //! the parent transformations
    Transform* parent;

    //! the translation of the entity
    glm::vec3 translation;
    //! the rotation of the entity
    glm::vec3 rotation;
    //! the scale of the entity
    glm::vec3 scale;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /** Creates a new transform component
    @param id the identifier of the component
    @param t the initial translation
    @param r the initial rotation
    @param s the initial scale
    @param axisSpace the axis space to use for computing the transform */
    Transform(
              const std::string           id,
              const glm::vec3&            t,
              const glm::vec3&            r,
              const glm::vec3&            s,
                    axis_space::AxisSpace axisSpace = axis_space::LOCAL );

    /** Creates a new transform component with a parent
    @param id the identifier of the component
    @param p the parent transform
    @param t the initial translation
    @param r the initial rotation
    @param s the initial scale
    @param axisSpace the axis space to use for computing the transform */
    Transform(
              const std::string           id,
                    Transform*            p,
              const glm::vec3&            t,
              const glm::vec3&            r,
              const glm::vec3&            s,
                    axis_space::AxisSpace axisSpace = axis_space::LOCAL );

    /** Creates a new component by copying from another and providing a new
    identifier
    @param id the new identifier
    @param other the other component to copy from */
    Transform( const std::string& id, const Transform& other );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    // ##DEPRECATED
    /** @return the axis space being used by this transform */
    axis_space::AxisSpace getAxisSpace() const;

    // ##DEPRECATED
    /** Compute the translation values to be applied taking into regards the
    parent transform and the axis space.
    @return the computed translation */
    glm::vec3 computeTranslation() const;

    // ##DEPRECATED
    /** Compute the rotation values to be applied taking into regards the
    parent transform and the axis space.
    @return the computed rotation */
    glm::vec3 computeRotation() const;


    // ##DEPRECATED
    /** Compute the scale values to be applied taking into regards the parent
    transform and the axis space.
    @return the computed scale */
    glm::vec3 computeScale() const;

    /** Applies the transform to the given matrix */
    void apply( glm::mat4& matrix );

    /** Applies the transform in reverse to the given matrix */
    void applyReverse( glm::mat4& matrix );

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the axis space to use
    axis_space::AxisSpace m_axisSpace;
};

} // namespace omi

#endif
