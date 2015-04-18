#ifndef OMICRON_COMPONENT_UPDATABLE_UPDATABLE_H_
#   define OMICRON_COMPONENT_UPDATABLE_UPDATABLE_H_

#include "src/omicron/component/Component.hpp"

namespace omi {

/***********************************************************************\
| Abstract class that defines a component that gets updated each frame. |
\***********************************************************************/
class Updatable : public Component {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Super constructor
    @ param id the identifier of the component */
    Updatable(const std::string& id) :
        Component(id) {
    }

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~Updatable() {
    }

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    virtual component::Type getType() const {

        return component::UPDATABLE;
    }

    /** #Hidden
    Updates this component */
    virtual void update() = 0;
};

} // namespace omi

#endif