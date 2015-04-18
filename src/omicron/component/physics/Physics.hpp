#ifndef OMICRON_COMPONENT_PHYSICS_PHYSICS_H_
#   define OMICRON_COMPONENT_PHYSICS_PHYSICS_H_

#include "src/omicron/component/Component.hpp"

namespace omi {

/***************************************************\
| Abstract class for components relating to physics |
\***************************************************/
class Physics : public Component {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Super constructor
    @ param id the identifier of the component */
    Physics( const std::string& id ) :
        Component( id )
    {
    }

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~Physics()
    {
    }

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    virtual component::Type getType() const
    {
        return component::PHYSICS;
    }
};

} // namespace omi

#endif
