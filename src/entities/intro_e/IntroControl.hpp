#ifndef HERETIC_ENTITIES_INTRO_INTROCONTROL_HPP_
#   define HERETIC_ENTITIES_INTRO_INTROCONTROL_HPP_

#include "src/omicron/entity/Entity.hpp"

//------------------------------------------------------------------------------
//                                  ENUMERATORS
//------------------------------------------------------------------------------

namespace intro
{
enum State
{
    TITLE_FADE = 0,
    TITLE_WAIT,
    INFO
};
} // namespace intro

class IntroControl : public omi::Entity
{
public:

    /** #Override */
    void init();

    /** #Override */
    void update();

    bool isDone();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    intro::State m_state;
    float m_fader;
    float m_waiter;
    bool m_done;

    omi::Transform* m_sunRot;

    omi::Text* titleMainText;
    omi::Text* titleUnderText;

    omi::Sprite* m_storySprite;
};

#endif
