#include "SoundResource.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

SoundResource::SoundResource(
              resource_group::ResourceGroup resourceGroup,
        const std::string&                  filePath,
              unsigned                      instances) :
    Resource   (resourceGroup),
    m_filePath (filePath),
    m_instances(instances) {
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

SoundResource::~SoundResource() {
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void SoundResource::load() {

    if (!m_loaded) {

        // add to the sound pool and get the id back
        m_id = SoundPool::load(m_filePath, m_instances);
        m_loaded = true;
    }
}

void SoundResource::release() {

    if (m_loaded) {

        // remove from the sound pool
        SoundPool::release(m_id);
        m_loaded = false;
    }
}

unsigned SoundResource::get() const {

    if (!m_loaded) {

        std::cout << "attempted to get unloaded sound" << std::endl;

        //TODO: throw an exception
    }

    return m_id;
}

} // namespace omi
