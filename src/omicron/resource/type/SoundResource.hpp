#ifndef OMICRON_RESOURCE_TYPE_SOUNDRESOURCE_H_
#   define OMICRON_RESOURCE_TYPE_SOUNDRESOURCE_H_

#include "src/omicron/audio/SoundPool.hpp"
#include "src/omicron/resource/type/Resource.hpp"

namespace omi {

/***************************************************************\
| Contains the needed data to load a sound into the sound pool. |
\***************************************************************/
class SoundResource : public Resource {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new sound resource
    @param resourceGroup the resource group the sound is within
    @param filePath the location of the sound to load
    @param instances the number of instances of this sound to be stored in the
           sound pool */
    SoundResource(
                  resource_group::ResourceGroup resourceGroup,
            const std::string&                  filePath,
                  unsigned                      instances);

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~SoundResource();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void load();

    /** #Override */
    void release();

    /** @return the id of the sound */
    unsigned get() const;

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the file path to the sound
    std::string m_filePath;
    // the number of instances of this sound to store in the pool
    unsigned m_instances;

    // the id of the sound
    unsigned m_id;
};

}

#endif