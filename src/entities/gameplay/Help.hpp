#ifndef HERETIC_ENTITIES_GAMEPLAY_HELP_HPP_
#   define HERETIC_ENTITIES_GAMEPLAY_HELP_HPP_

#include "src/omicron/entity/Entity.hpp"

//------------------------------------------------------------------------------
//                                  ENUMERATORS
//------------------------------------------------------------------------------

namespace help
{
enum State
{
    TO_START = 0,
    FUNCTIONS,
    DESTROY,
    WIN,
    EXIT,
    DONE
};
} // namespace help

class Help : public omi::Entity
{
public:

/** #Override */
void init();

/** #Override */
void update();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    omi::Text* m_indexText;
    omi::Text* m_rotateText;
    omi::Text* m_zoomText;

    omi::Transform* m_tutPos;
    omi::Transform* m_tutPos2;

    omi::Sprite* m_funcSprite;
    omi::Sprite* m_destroySprite;
    omi::Sprite* m_winSprite;
    omi::Sprite* m_exitSprite;

    bool m_tutDone;
    float m_timer;
    help::State m_state;
};

#endif
