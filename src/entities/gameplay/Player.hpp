#ifndef HERETIC_ENTITIES_GAMEPLAY_PLAYER_HPP
#   define HERETIC_ENTITIES_GAMEPLAY_PLAYER_HPP

#include "src/omicron/entity/Entity.hpp"

class Player : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    Player();

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
