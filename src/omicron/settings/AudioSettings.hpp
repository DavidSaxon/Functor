#ifndef OMICRON_SETTINGS_AUDIO_SETTINGS_H_
#   define OMICRON_SETTINGS_AUDIO_SETTINGS_H_

#include "lib/Utilitron/MacroUtil.hpp"

namespace omi {

/***************************************************************************\
| An object that contains all audio related settings controlled by Omicron. |
\***************************************************************************/
class AudioSettings {
private:

    //--------------------------------------------------------------------------
    //                                RESTRICTIONS
    //--------------------------------------------------------------------------

    DISALLOW_COPY_AND_ASSIGN(AudioSettings);

public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates new audio settings initialised with the default values */
    AudioSettings();

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~AudioSettings();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Hidden
    Checks if a change has been made to the settings */
    bool check();

    /** @return if sounds have been disabled */
    bool isSoundDisabled() const;

    /** @return if music has been disabled */
    bool isMusicDisabled() const;

    /** @return the master volume of sounds  */
    float getSoundVolume() const;

    /** @return the master volume of music */
    float getMusicVolume() const;

    /** @param disabled whether sounds are disabled or not */
    void setSoundDisabled(bool disabled);

    /** @param disabled whether music is disabled or not */
    void setMusicDisabled(bool disabled);

    /** @param volume the master volume for sounds */
    void setSoundVolume(float volume);

    /** @param volume the master volume for music */
    void setMusicVolume(float volume);

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // if a setting has changed
    bool m_change;

    // if sounds are disabled
    bool m_soundDisabled;
    // if music disabled
    bool m_musicDisabled;
    // the volume of sounds
    float m_soundVolume;
    // the volume of music
    float m_musicVolume;
};

} // namespace omi

#endif