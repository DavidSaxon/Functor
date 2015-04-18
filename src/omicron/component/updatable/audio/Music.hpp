#ifndef OMICRON_COMPONENT_UPDATABLE_AUDIO_MUSIC_H_
#   define OMICRON_COMPONENT_UPDATABLE_AUDIO_MUSIC_H_

#include <iostream>
#include <SFML/Audio.hpp>

#include "src/omicron/Omicron.hpp"
#include "src/omicron/component/updatable/Updatable.hpp"

namespace omi {

class Music : public Updatable {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new music component
    @ param id the identifier of the component
    @ param filePath the path to the file to play
    @ param volume the initial volume of music
    @ param loop if playback of the music should loop or not */
    Music(const std::string& id,
          const std::string& filePath,
                float        volume,
                bool loop);

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~Music();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void update();

    /** Starts playback of the music */
    void play();

    /** Pauses playback of the music */
    void pause();

    /** Stops playback of the music */
    void stop();

    //---------------------------------GETTERS----------------------------------

    /** @return the volume of the music */
    float getVolume() const;

    /** @return if the music has stopped playing */
    bool isStopped() const;

    /** @return if the music is looping */
    bool isLooping() const;

    //---------------------------------SETTERS----------------------------------

    /** @param volume the new volume of the music */
    void setVolume(float volume);

    /** @param loop whether the music should loop or not */
    void setLoop(bool loop);

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the sfml music object
    sf::Music m_music;
    // the volume of the music
    float m_volume;
    // the looping mode of the music
    bool m_loop;
};

} // namespace omi

#endif
