#include "FPSManager.hpp"

namespace omi {

namespace {

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

// the length of a standard frame in milliseconds
static const float STD_FRAME_LENGTH = 16.0f;

} // namespace anonymous

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

FPSManager::FPSManager() :
    m_timeScale     (1.0f),
    m_fps           (0.0f),
    m_lastUpdateTime(util::time::getCurrentTime()) {
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

FPSManager::~FPSManager() {
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void FPSManager::update() {

    // get current time
    int64_t currentTime = util::time::getCurrentTime();
    // find delta time
    float deltaTime = static_cast<float>(currentTime - m_lastUpdateTime);
    // set the new last update time
    m_lastUpdateTime = currentTime;

    // calculate the time scale
    m_timeScale = deltaTime / STD_FRAME_LENGTH;
    // calculate the fps
    m_fps = util::time::MS_IN_SEC / deltaTime;

}

void FPSManager::zero() {

    m_lastUpdateTime = util::time::getCurrentTime();
}


float FPSManager::getTimeScale() const {

    return m_timeScale;
}

float FPSManager::getFPS() {

    return m_fps;
}

} // namespace omi
