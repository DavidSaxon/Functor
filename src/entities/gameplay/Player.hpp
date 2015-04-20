#ifndef HERETIC_ENTITIES_GAMEPLAY_PLAYER_HPP
#   define HERETIC_ENTITIES_GAMEPLAY_PLAYER_HPP

#include "src/omicron/entity/Entity.hpp"

//------------------------------------------------------------------------------
//                              FORWARD DECLARATIONS
//------------------------------------------------------------------------------

class Gui;
class World;

//------------------------------------------------------------------------------
//                                  ENUMERATORS
//------------------------------------------------------------------------------

namespace gameplay
{
// the gameplay state
enum State
{
    PLANET_SELECT = 0,
    TRANS_TO_PLANET,
    PLANET_ORBIT
};
enum FuncType
{
    X_X = 0,
    MX_X,
    SIN,
    COS, //
    TAN, //
    RAND
};
} // namespace gameplay

class Player : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    Player( Gui* gui, const std::vector<World*>& worlds );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void init();

    /** #Override */
    void update();

    void goLevel();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the current gameplay state
    gameplay::State m_state;

    // the gui entity;
    Gui* m_gui;

    // the worlds in the current stage
    std::vector<World*> m_worlds;
    // the currently selected world
    World* m_world;

    // the central player point
    omi::Transform* m_centrePos;
    // the distance from the centre point
    omi::Transform* m_distT;
    // the focus point of the camera
    omi::Transform* m_camFocus;
    // the position of the camera
    omi::Transform* m_camPos;

    float m_generatingFuncs;

    bool m_genTime;

    gameplay::FuncType m_leftFunc;
    gameplay::FuncType m_RightFunc;

    float m_genDistance;
    float m_power;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void look();

    // do planet selection
    void planetSelect();

    // do transition to planet
    void transToPlanet();

    // do planet orbit
    void planetOrbit();

    void attack();

    void initComponents();
};

#endif
