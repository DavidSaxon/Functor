#ifndef OMICRON_RESOURCE_TYPE_TEXTRESOURCE_HPP_
#   define OMICRON_RESOURCE_TYPE_TEXTRESOURCE_HPP_

#include "src/omicron/resource/ResourceManager.hpp"

class ResourceManager;

#include "src/omicron/component/renderable/Text.hpp"
#include "src/omicron/resource/type/Resource.hpp"

namespace omi {

/****************************************\
| Contains the data needed to load text. |
\****************************************/
class TextResource : public Resource {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new text resource
    @param resourceGroup the resource group of the text
    @param layer the layer of the text
    @param material the resource id of the text's material
    @param font the resource id of the font to use
    @param str the string of the text
    @param size the initial size of the text */
    TextResource(
            resource_group::ResourceGroup resourceGroup,
            int layer,
            const std::string& material,
            const std::string& font,
            const std::string& str,
            float size );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void load();

    /** #Override */
    void release();

    /** @return the loaded text
    @param id the the component  identifier of the text
    @param transform the transform to use for the text */
    Text* get( const std::string& id, Transform* transform ) const;

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the layer of the text
    int m_layer;
    // the resource id of the text's material
    std::string m_material;
    // the resource id of the text's font
    std::string m_font;
    // the string of the text
    std::string m_str;
    // the size of the font
    float m_size;

};

} // namespace omi

#endif
