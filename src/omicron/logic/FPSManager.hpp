#ifndef OMICRON_FPS_MANAGER_FPSMANAGER_H_
#   define OMICRON_FPS_MANAGER_FPSMANAGER_H_

#include "lib/Utilitron/MacroUtil.hpp"
#include "lib/Utilitron/TimeUtil.hpp"
#include "lib/Utilitron/TypeUtil.hpp"

namespace omi {

/**************************************************************************\
| Records the current FPS and provides a time scale to apply to time-based |
| scene evolution.                                                         |
\**************************************************************************/
class FPSManager {
private:

    //--------------------------------------------------------------------------
    //                                RESTRICTIONS
    //--------------------------------------------------------------------------

    DISALLOW_COPY_AND_ASSIGN(FPSManager);

public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new FPSManager */
    FPSManager();

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~FPSManager();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Hidden
    Updates the FPS manager, recalculating the current time-scale and FPS */
    void update();

    /** #Hidden
    Zeros the FPS manager to begin recalculating (used to avoid first frame lag
    after loading) */
    void zero();

    /** @return the current time scale */
    float getTimeScale() const ;

    /** @return the current fps */
    float getFPS();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the current time scale
    float m_timeScale;
    // the current fps
    float m_fps;

    //the last time a logic cycle of the engine ran
    util::int64 m_lastUpdateTime;
};

} //namespace omi

#endif
