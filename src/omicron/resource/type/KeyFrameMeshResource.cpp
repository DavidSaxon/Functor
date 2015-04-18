#include "KeyFrameMeshResource.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

KeyFrameMeshResource::KeyFrameMeshResource(
        resource_group::ResourceGroup resourceGroup,
        int                           layer,
        const std::string&            material,
        const std::string&            filePath ) :
    Resource  ( resourceGroup ),
    m_layer   ( layer ),
    m_material( material ),
    m_filePath( filePath )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void KeyFrameMeshResource::load()
{
    if ( !m_loaded )
    {
        loader::geoFromKeyFrameWavefront(
                m_filePath,
                m_geoMap,
                m_frameMap,
                m_defaultAni
        );
        m_loaded = true;
    }
}

void KeyFrameMeshResource::release()
{
    if ( m_loaded )
    {
        for ( std::map<std::string, std::vector<Geometry*>>::iterator it
              = m_geoMap.begin(); it != m_geoMap.end(); ++it )
        {
            while ( !it->second.empty() )
            {
                delete it->second.back();
                it->second.pop_back();
            }
        }
        m_geoMap.clear();
        m_frameMap.clear();
        m_defaultAni = "";

        m_loaded = false;
    }
}

KeyFrameMesh* KeyFrameMeshResource::get(
        const std::string& id, Transform* transform ) const
{
    if ( !m_loaded )
    {
        std::cout << "attempted to get unloaded key frame mesh" << std::endl;
        //TODO: throw an exception
    }

    return new KeyFrameMesh(
        id, m_layer, transform, m_geoMap, m_frameMap, m_defaultAni,
        ResourceManager::getMaterial( m_material )
    );
}

} // namespace omi
