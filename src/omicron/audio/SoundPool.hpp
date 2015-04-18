#ifndef OMICRON_AUDIO_SOUNDPOOL_H_
#   define OMICRON_AUDIO_SOUNDPOOL_H_

#include <iostream>
#include <map>
#include <SFML/Audio.hpp>
#include <vector>

#include "src/omicron/Omicron.hpp"
#include "src/omicron/resource/ResourceServer.hpp"

namespace omi {

/*************************************************************\
| Static object that manages storing of and access to sounds. |
\*************************************************************/
class SoundPool {
private:

    //--------------------------------------------------------------------------
    //                                RESTRICTIONS
    //--------------------------------------------------------------------------

    DISALLOW_CONSTRUCTION(SoundPool);

    /**************************************************************************\
    | Stores a set of instances of sounds and manages which instance should be |
    | distributed next.                                                        |
    \**************************************************************************/
    struct SoundBank {
    public:

        //----------------------------------------------------------------------
        //                              CONSTRUCTOR
        //----------------------------------------------------------------------

        /** Creates an empty sound bank */
        SoundBank() {
        }

        /** Creates a new bank of loaded sounds
        @param filePath the location of the sound
        @param instances the number of instances of the sound in the bank */
        SoundBank(const std::string& filePath, unsigned instances) :
            m_instance   (0),
            m_numInstance(instances) {

            // open the file using the resource server
            VirtualFile file;
            ResourceServer::get( filePath, file );

            if ( !m_buffer.loadFromMemory( file.getData(), file.getSize() ) )
            {
                std::cout << "loading sound failed" << std::endl;
            }

            // load the given number of instances of the sound
            for (unsigned i = 0; i < m_numInstance; ++i) {

                m_bank.push_back(sf::Sound());
                // m_bank[i].setBuffer(m_buffer);
            }
        }

        //----------------------------------------------------------------------
        //                               DESTRUCTOR
        //----------------------------------------------------------------------

        ~SoundBank() {

            // TODO: unload the sound
        }

        //----------------------------------------------------------------------
        //                        PUBLIC MEMBER FUNCTIONS
        //----------------------------------------------------------------------

        /** Plays the next instance of the sound
        @param loop whether the sound should loop or not
        @param volume the volume to play the sound at
        @return the instance of the sound being played */
        inline unsigned playNext(bool loop, float volume) {

            // TODO: figure out why the buffer can't be set in the constructor
            m_bank[m_instance].setBuffer(m_buffer);
            // play current instance
            m_bank[m_instance].setLoop(loop);
            m_bank[m_instance].setVolume(
                (audioSettings.getSoundVolume() * volume) * 100.0f);
            m_bank[m_instance].play();

            // increment instance
            unsigned rInstance = m_instance;
            m_instance = (m_instance + 1) % m_numInstance;

            return rInstance;
        }

        /** Stops the given instance of the sound
        @param instance the instance to stop */
        inline void stop(unsigned instance) {

            m_bank[m_instance].stop();
        }

    private:

        //----------------------------------------------------------------------
        //                               VARIABLES
        //----------------------------------------------------------------------

        // the sound buffer
        sf::SoundBuffer m_buffer;
        // the list of instances of the sound
        std::vector<sf::Sound> m_bank;
        // the current instance to play
        unsigned m_instance;
        // the number of instances
        unsigned m_numInstance;
    };

public:

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Hidden
    Adds a sound to the sound pool
    @param filePath the location of the sound to add
    @param instances the number of instances of this sound that will be loaded
           into the sound pool
    @return the id of the sound */
    static unsigned load(const std::string& filePath, unsigned instances);

    /** #Hidden
    Removes a sound from the sound pool
    @param id the identifier of the sound to remove */
    static void release(unsigned id);

    /** Plays a sound
    @param id the identifier of the sound to play
    @param loop whether the sound should loop or not
    @param volume the volume to play the sound at
    @return the instances of the sound playing */
    static unsigned play(unsigned id, bool loop, float volume);

    /** Stops a sound
    @param id the identifier of the sound to stop
    @param instance the instance of the sound to stop */
    static void stop(unsigned id, unsigned instance);


private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the pool of sounds
    static std::map<unsigned, SoundBank> m_pool;

    // the next id to be assigned to a sound
    static unsigned m_currentId;
};

} // namespace omi

#endif
