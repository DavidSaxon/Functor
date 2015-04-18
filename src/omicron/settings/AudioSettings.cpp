#include "AudioSettings.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

AudioSettings::AudioSettings() :
    m_change       (true),
    m_soundDisabled(false),
    m_musicDisabled(false),
    m_soundVolume  (1.0f),
    m_musicVolume  (1.0f) {
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

AudioSettings::~AudioSettings() {
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

bool AudioSettings::check() {

    return m_change;
}

bool AudioSettings::isSoundDisabled() const {

    return m_soundDisabled;
}

bool AudioSettings::isMusicDisabled() const {

    return m_musicDisabled;
}

float AudioSettings::getSoundVolume() const {

    return m_soundVolume;
}

float AudioSettings::getMusicVolume() const {

    return m_musicVolume;
}

void AudioSettings::setSoundDisabled(bool disabled) {

    m_soundDisabled = disabled;
    m_change = true;
}

void AudioSettings::setMusicDisabled(bool disabled) {

    m_musicDisabled = disabled;
    m_change = true;
}

void AudioSettings::setSoundVolume(float volume) {

    m_soundVolume = volume;
    m_change = true;
}

void AudioSettings::setMusicVolume(float volume) {

    m_musicVolume = volume;
    m_change = true;
}

} // namespace omi