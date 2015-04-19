#ifndef HERETIC_ENTITIES_GAMEPLAY_ENVIRONMENT_TOWER_HPP_
#   define HERETIC_ENTITIES_GAMEPLAY_ENVIRONMENT_TOWER_HPP_

#include "src/omicron/entity/Entity.hpp"

//------------------------------------------------------------------------------
//                              FORWARD DECLARATIONS
//------------------------------------------------------------------------------

class World;

class Tower : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    Tower( omi::Transform* parentPos, float height );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void init();

    void update();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the parent position
    omi::Transform* m_parentPos;
    // the height of the tower
    float m_height;

    // the position of the tower
    omi::Transform* m_pos;

    // the meshes of the tower
    omi::Mesh* m_mesh1;
    omi::Mesh* m_mesh2;
    omi::Mesh* m_mesh3;
};

#endif
