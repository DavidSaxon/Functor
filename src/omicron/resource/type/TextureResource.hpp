#ifndef OMICRON_RESOURCE_TYPE_TEXTURERESOURCE_H_
#   define OMICRON_RESOURCE_TYPE_TEXTURERESOURCE_H_

#include <memory>

#include "src/omicron/rendering/shading/Texture.hpp"
#include "src/omicron/resource/type/Resource.hpp"

namespace omi {

namespace texture {

enum Flag {
    CLAMP       = 1,
    SHOW_PIXELS = 2
};

} // namespace texture

/*********************************************\
| Contains the needed data to load a texture. |
\*********************************************/
class TextureResource : public Resource {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /** Creates a new plain texture resource
    @param resourceGroup the resource group of the texture
    @param filePath the path to the image file to use for the texture */
    TextureResource(      resource_group::ResourceGroup resourceGroup,
                    const std::string&                  filePath,
                          unsigned                      flags );

    /** Creates an animated texture resource
    @param resourceGroup the resource group of the texture
    @param filePath the path to the image file to use for the texture
    @param frameRate the playback speed of the animation
    @param repeat if the animation should repeat
    @param begin the beginning frame if the animation
    @param end the ending frame of the animation */
    TextureResource(      resource_group::ResourceGroup resourceGroup,
                    const std::string&                  filePath,
                          unsigned                      frameRate,
                          bool                          repeat,
                          unsigned                      begin,
                          unsigned                      end,
                          unsigned                      flags );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void load();

    /** #Override */
    void release();

    /** @return the loaded texture */
    Texture* get() const;

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the type of texture this is
    tex::Type m_type;
    // the file path to load the texture from
    std::string m_filePath;

    // the texture flags
    unsigned m_flags;
    // if the texture should clamp to edges
    bool m_clamp;
    // if the texture should not interpolate when scaled
    bool m_showPixels;

    //animation variables
    unsigned m_frameRate;
    bool m_repeat;
    unsigned m_begin;
    unsigned m_end;

    // the omicron texture
    std::unique_ptr<Texture> m_texture;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Parses the texture flags */
    void parseFlags();
};

} // namespace omi

#endif
