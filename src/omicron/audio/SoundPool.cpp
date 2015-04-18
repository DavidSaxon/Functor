#include "SoundPool.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

std::map<unsigned, SoundPool::SoundBank> SoundPool::m_pool;
unsigned SoundPool::m_currentId = 0;

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

unsigned SoundPool::load(const std::string& filePath, unsigned instances) {

    // create the bank at the next available id
    m_pool.insert(std::make_pair(
        m_currentId,
        SoundBank(filePath, instances)
        )
    );

    // increment id
    unsigned rId = m_currentId;
    ++m_currentId;

    return rId;
}

void SoundPool::release(unsigned id) {

    m_pool.erase(m_pool.find(id));
}

unsigned SoundPool::play(unsigned id, bool loop, float volume) {

    // don't play if sounds are disabled
    if (audioSettings.isSoundDisabled()) {

        return -1;
    }

    return m_pool[id].playNext(loop, volume);
}

void SoundPool::stop(unsigned id, unsigned instance) {

    m_pool[id].stop(instance);
}

} // namespace omi
