#ifndef OMICRON_ENTITIES_START_UP_OMICRONLOGO_H_
#   define OMICRON_ENTITIES_START_UP_OMICRONLOGO_H_

#include <stdlib.h>

#include "src/omicron/entity/Entity.hpp"

/******************************************\
| Displays the Omicron start up cinematic. |
\******************************************/
class OmicronLogo : public omi::Entity {
private:

    // the stages of the cinematic
    enum Stage {
        WAIT_ONE,
        TEXT_ENTER,
        FLARE_EXPAND,
        FLARE_FADE,
        GLOW,
        DONE
    };

public:

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void init();

    /** #Override */
    void update();

    /** @return if the cinematic has finished */
    bool done();

private:

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Creates the components */
    void initComponents();

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the transform of the camera
    omi::Transform* m_camT;
    // the shake on the camera
    float m_camShake;

    // the transform of the bottom of the text
    omi::Transform* m_textBottomT;
    // the transform of the top of the text
    omi::Transform* m_textTopT;
    // the transform of the long lens flare
    omi::Transform* m_flareLongT;
    // the transform of the centre lens flare
    omi::Transform* m_flareCentreT;

    // the material of the long lens flare
    omi::Material* m_flareLongMat;
    // the material of the centre lens flare
    omi::Material* m_flareCentreMat;
    // the material of the glow
    omi::Material* m_glowMat;
    // the material of the powered by
    omi::Material* m_poweredByMat;

    // the stage the cinematic is in
    Stage m_stage;
    // the timer
    float m_timer;
};

#endif