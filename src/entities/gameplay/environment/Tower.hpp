#ifndef HERETIC_ENTITIES_GAMEPLAY_ENVIRONMENT_TOWER_HPP_
#   define HERETIC_ENTITIES_GAMEPLAY_ENVIRONMENT_TOWER_HPP_

#include "src/omicron/entity/Entity.hpp"

//------------------------------------------------------------------------------
//                                  ENUMERATORS
//------------------------------------------------------------------------------

namespace tower
{
enum Colour
{
    BLUE = 0,
    RED
};
enum Strength
{
    WEAK = 0,
    NORMAL = 1,
    STRONG = 2
};
} // namespace tower

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

    Tower(
            omi::Transform* parentPos,
            tower::Colour colour,
            tower::Strength strength,
            float height );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void init();

    void update();

    tower::Colour getColour() const;

    void setHeight( float height );

    float getChangeDis() const;

    void destroy();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the parent position
    omi::Transform* m_parentPos;
    // the colour of the tower block
    tower::Colour m_colour;
    // the strength of the tower block
    tower::Strength m_strength;
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
