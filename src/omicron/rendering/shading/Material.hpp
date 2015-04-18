#ifndef OMICRON_RENDERING_SHADING_MATERIAL_H_
#   define OMICRON_RENDERING_SHADING_MATERIAL_H_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include <iostream>

#include "lib/glm/glm.hpp"

#include "src/omicron/rendering/shading/Shader.hpp"
#include "src/omicron/rendering/shading/Texture.hpp"
#include "src/omicron/rendering/shading/material_property/Glow.hpp"
#include "src/omicron/rendering/shading/material_property/Specular.hpp"

namespace omi {

namespace material {

enum Flags {
    SHADELESS = 1
};

} // namespace material

/*********************************************************\
| A material contains all the shading data for an object. |
\*********************************************************/
class Material {
public:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    //! the shader used for the material
    Shader shader;
    //! the colour of the material
    glm::vec4 colour;
    //! a pointer to the texture of the material
    Texture* texture;
    //! the specular property of the material
    Specular* specular;
    //! the glow property of the material
    Glow* glow;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /** Creates a material with the default set up */
    Material();

    /** Creates a material using the given values
    @param a_shader the shader of the material
    @param a_colour the colour of the material
    @param a_texture the texture of the material
    @param flags the flags of the material */
    Material( const Shader&    a_shader,
              const glm::vec4& a_colour,
                    Texture*   a_texture,
                    unsigned   flags );

    /** Creates a copy of the given material
    @param other the material to copy from */
    Material( const Material& other );

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~Material();

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /** Copies the values of the given material to this material
    @param other the material to copy from */
    const Material& operator=( const Material& other );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Updates the material */
    void update();

    /** @return if the material is visible */
    bool isVisible() const;

    /** @return if the material is unaffected by light */
    bool isShadeless() const;

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the material flags
    unsigned m_flags;

    // if the material is not affected by light
    bool m_shadeless;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Parses the material flags */
    void parseFlags();
};

} // namespace omi

#endif
