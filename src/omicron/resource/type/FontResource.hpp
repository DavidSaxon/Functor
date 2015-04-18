#ifndef OMICRON_RESOURCE_TYPE_FONTRESOURCE_HPP_
#   define OMICRON_RESOURCE_TYPE_FONTRESOURCE_HPP_

#include <memory>

#include "src/omicron/resource/type/Resource.hpp"

namespace omi {

/******************************************\
| Contains the data needed to load a font. |
\******************************************/
class FontResource : public Resource {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new font resource
    @param resourceGroup the resource group of the font
    @param freeType a pointer to the free type library object
    @param filePath the file path to the font */
    FontResource(
            resource_group::ResourceGroup resourceGroup,
            FT_Library* freeType,
            const std::string& filePath );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void load();

    /** #Override */
    void release();

    /** @return the loaded font */
    Font* get() const;

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the FreeType library object
    FT_Library* m_freeType;
    // the file path to load the font from
    std::string m_filePath;

    // the loaded font object
    std::unique_ptr<Font> m_font;
};

} // namespace omi

#endif
