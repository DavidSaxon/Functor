#ifndef HERETIC_ENTITIES_GAMEPLAY_PLAYER_HPP
#   define HERETIC_ENTITIES_GAMEPLAY_PLAYER_HPP

#include "src/omicron/entity/Entity.hpp"

//------------------------------------------------------------------------------
//                              FORWARD DECLARATIONS
//------------------------------------------------------------------------------

class World;

class Player : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    Player( const std::vector<World*>& worlds );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void init();

    /** #Override */
    void update();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the worlds in the current stage
    std::vector<World*> m_worlds;

    // the focus point of the camera
    omi::Transform* m_camFocus;
    // the position of the camera
    omi::Transform* m_camPos;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void look();

    void initComponents();
};

#endif
