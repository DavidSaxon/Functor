#include "Renderable.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

Shader Renderable::shadowShader;
Shader Renderable::glowShader;
Shader Renderable::selectionShader;

namespace {

// the bias matrix for calculating the shadow matrix
static const glm::mat4 BIAS_MATRIX(
        0.5f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f
);

} // namespace omi

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Renderable::Renderable(
        const std::string& id,
              int          layer,
              Transform*   transform,
        const Material     material )
    :
    Component     ( id ),
    visible       ( true ),
    castShadow    ( true ),
    overlay       ( false ),
    gui           ( false ),
    selectable    ( false ),
    selected      ( false ),
    m_layer       ( layer ),
    m_transform   ( transform ),
    m_material    ( material ),
    m_doVisCheck  ( true ),
    m_onlyVisCheck( false ),
    m_visCam      ( false )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Renderable::update()
{
    // update the material
    m_material.update();

    applyTransformations();
}

void Renderable::render(
        Camera* camera,
        Camera* shadowCamera,
        const LightData& lightData )
{
    // only render if visible and there is a camera
    if ( !visible                ||
         !m_material.isVisible() ||
         m_onlyVisCheck          ||
         camera == NULL )
    {
        return;
    }

    calculateMatrices( camera );
    setShader( lightData, camera, shadowCamera );
    draw();
    unsetShader();
}

void Renderable::renderShadow( Camera* camera )
{
    // TODO: check if this projects shadows

    // only render if visible and there is a camera
    if ( !visible                ||
         !m_material.isVisible() ||
         m_onlyVisCheck          ||
         camera == NULL          ||
         !castShadow )
    {
        return;
    }

    calculateMatrices( camera );

    // get the OpenGL program
    GLuint program = shadowShader.getProgram();
    // use the shader
    glUseProgram( program );

    // pass in the matrix to the shader
    glUniformMatrix4fv(
        glGetUniformLocation( program, "u_modelViewProjectionMatrix" ),
        1, GL_FALSE, &m_modelViewProjectionMatrix[0][0] );

    draw();
    unsetShader();
}

void Renderable::renderGlow( Camera* camera )
{
    // only render if visible and there is a camera
    if ( !visible                ||
         !m_material.isVisible() ||
         m_onlyVisCheck          ||
         camera == NULL )
    {
        return;
    }

    calculateMatrices( camera );

    // get the OpenGL program
    GLuint program = glowShader.getProgram();
    // use the shader
    glUseProgram( program );

    // pass in the matrices to the shader
    glUniformMatrix4fv(
        glGetUniformLocation( program, "u_modelViewProjectionMatrix" ),
        1, GL_FALSE, &m_modelViewProjectionMatrix[0][0] );

    // get the colour based on glow component
    glm::vec3 colour( 0.0f, 0.0f, 0.0f );
    float brightness = 1.0f;
    if ( m_material.glow != NULL )
    {
        colour =
                m_material.glow->getColour() * m_material.glow->getBrightness();
    }

    // pass in colour to the shader
    glUniform4f(
        glGetUniformLocation( program, "u_colour" ),
        colour.r,
        colour.g,
        colour.b,
        1.0f
    );

    // texture
    if ( m_material.glow != NULL && m_material.glow->getTexture() != NULL )
    {
        glUniform1i( glGetUniformLocation( program, "u_hasTexture" ), 1 );
        glBindTexture( GL_TEXTURE_2D,
                m_material.glow->getTexture()->getId() );
    }
    else
    {
        glUniform1i( glGetUniformLocation( program, "u_hasTexture" ), 0 );
        glBindTexture( GL_TEXTURE_2D, 0 );
    }

    // draw
    draw();
    unsetShader();
}

void Renderable::renderSelectable(
        Camera* camera,
        unsigned char red,
        unsigned char green,
        unsigned char blue )
{
    // don't bother rendering if there is no camera
    if ( camera == NULL          ||
         !visible                ||
         !m_material.isVisible() ||
         m_onlyVisCheck )
    {
        return;
    }

    calculateMatrices( camera );

    // shader shit
    GLuint program = selectionShader.getProgram();
    glUseProgram( program );
    // matrix
    glUniformMatrix4fv(
        glGetUniformLocation( program, "u_modelViewProjectionMatrix" ),
        1, GL_FALSE, &m_modelViewProjectionMatrix[0][0] );
    // colour
    glUniform4f(
        glGetUniformLocation( program, "u_colour" ),
        static_cast<float>( red )   / 255.0f,
        static_cast<float>( green ) / 255.0f,
        static_cast<float>( blue )  / 255.0f,
        1.0f
    );
    // texture
    if ( m_material.texture != NULL )
    {
        glUniform1i( glGetUniformLocation( program, "u_hasTexture" ), 1 );
        glBindTexture( GL_TEXTURE_2D, m_material.texture->getId() );
    }
    else
    {
        glUniform1i( glGetUniformLocation( program, "u_hasTexture" ), 0 );
        glBindTexture( GL_TEXTURE_2D, 0 );
    }

    // draw
    draw();

    // clean up
    glUseProgram( 0 );
    glBindTexture( GL_TEXTURE_2D, 0 );
}

void Renderable::renderVisCheck(
        Camera* camera,
        unsigned char red,
        unsigned char green,
        unsigned char blue )
{
    // don't bother rendering if there is no camera
    if ( camera == NULL          ||
         !visible                ||
         !m_material.isVisible() ||
         !m_doVisCheck )
    {
        return;
    }

    calculateMatrices( camera );

    // shader shit
    GLuint program = selectionShader.getProgram();
    glUseProgram( program );
    // matrix
    glUniformMatrix4fv(
        glGetUniformLocation( program, "u_modelViewProjectionMatrix" ),
        1, GL_FALSE, &m_modelViewProjectionMatrix[0][0] );
    // colour
    glUniform4f(
        glGetUniformLocation( program, "u_colour" ),
        static_cast<float>( red )   / 255.0f,
        static_cast<float>( green ) / 255.0f,
        static_cast<float>( blue )  / 255.0f,
        1.0f
    );
    // texture
    if ( m_material.texture != NULL )
    {
        glUniform1i( glGetUniformLocation( program, "u_hasTexture" ), 1 );
        glBindTexture( GL_TEXTURE_2D, m_material.texture->getId() );
    }
    else
    {
        glUniform1i( glGetUniformLocation( program, "u_hasTexture" ), 0 );
        glBindTexture( GL_TEXTURE_2D, 0 );
    }

    // draw
    draw();

    // clean up
    glUseProgram( 0 );
    glBindTexture( GL_TEXTURE_2D, 0 );
}

void Renderable::ignoreLight( const std::string& lightId )
{
    m_ignoreLights.push_back( lightId );
}

//-----------------------------------GETTERS------------------------------------

component::Type Renderable::getType() const
{
    return component::RENDERABLE;
}

int Renderable::getLayer() const
{
    return m_layer;
}

Transform* Renderable::getTransform()
{
    return m_transform;
}

Material& Renderable::getMaterial()
{
    return m_material;
}

bool Renderable::getDoVisCheck() const
{
    return m_doVisCheck;
}

bool Renderable::getOnlyVisCheck() const
{
    return m_onlyVisCheck;
}

bool Renderable::getVisCam() const
{
    return m_visCam;
}

//-----------------------------------SETTERS------------------------------------

void Renderable::setLayer( int layer )
{
    m_layer = layer;
}

void Renderable::setTransform( Transform* transform )
{
    m_transform = transform;
}

void Renderable::setDoVisCheck( bool state )
{
    m_doVisCheck = state;
}

void Renderable::setOnlyVisCheck( bool state )
{
    m_onlyVisCheck = state;
}

void Renderable::setVisCam( bool vis )
{
    m_visCam = vis;
}

//------------------------------------------------------------------------------
//                           PROTECTED MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Renderable::applyTransformations()
{
    // apply identity to model matrix
    m_modelMatrix = glm::mat4( 1.0f );

    // do nothing if the transform is null
    if ( !m_transform )
    {
        return;
    }

    m_transform->apply( m_modelMatrix );
}

void Renderable::calculateMatrices( Camera* camera )
{
    // get the view matrix from the camera
    m_viewMatrix = camera->getViewMatrix();
    // calculate the model, view matrix
    m_modelViewMatrix = camera->getViewMatrix() * m_modelMatrix;
    // calcaulate the normal matrix
    m_normalMatrix = glm::mat3( glm::transpose( glm::inverse( m_modelViewMatrix ) ) );
    //calculate the model, view, projection matrix
    m_modelViewProjectionMatrix =
        camera->getProjectionMatrix() *
        camera->getViewMatrix() *
        m_modelMatrix;
}

void Renderable::setShader(
        const LightData& lightData,
        Camera* camera,
        Camera* shadowCamera )
{
    // get the OpenGL program
    GLuint program = m_material.shader.getProgram();
    // use the shader
    glUseProgram( program );

    // pass in the matrices to the shader
    glUniformMatrix4fv(
        glGetUniformLocation( program, "u_modelMatrix" ),
        1, GL_FALSE, &m_modelMatrix[0][0] );
    glUniformMatrix4fv(
        glGetUniformLocation( program, "u_viewMatrix" ),
        1, GL_FALSE, &m_viewMatrix[0][0] );
    glUniformMatrix4fv(
        glGetUniformLocation( program, "u_modelViewMatrix" ),
        1, GL_FALSE, &m_modelViewMatrix[0][0] );
    glUniformMatrix3fv(
        glGetUniformLocation( program, "u_normalMatrix" ),
        1, GL_FALSE, &m_normalMatrix[0][0] );
    glUniformMatrix4fv(
        glGetUniformLocation( program, "u_modelViewProjectionMatrix" ),
        1, GL_FALSE, &m_modelViewProjectionMatrix[0][0] );

    // pass in colour to the shader
    glUniform4f(
        glGetUniformLocation( program, "u_colour" ),
        m_material.colour.r,
        m_material.colour.g,
        m_material.colour.b,
        m_material.colour.a
    );

    // texture
    glActiveTexture( GL_TEXTURE0 );
    glUniform1i( glGetUniformLocation( program, "u_texture" ), 0 );
    if ( m_material.texture != NULL )
    {
        glUniform1i( glGetUniformLocation( program, "u_hasTexture" ), 1 );
        glBindTexture( GL_TEXTURE_2D, m_material.texture->getId() );
    }
    else
    {
        glUniform1i( glGetUniformLocation( program, "u_hasTexture" ), 0 );
        glBindTexture( GL_TEXTURE_2D, 0 );
    }
    // don't invert texture colours
    glUniform1i( glGetUniformLocation( program, "u_invertTexCol" ), 0 );

    // pass in camera exposure
    glUniform1f(
        glGetUniformLocation( program, "u_exposure" ),
        camera->getExposure()
    );

    // lighting
    if ( m_material.isShadeless() )
    {
        // material is not affected by light
        glUniform1i( glGetUniformLocation( program, "u_shadeless" ), 1 );
    }
    else
    {
        // material is affected by light
        glUniform1i( glGetUniformLocation( program, "u_shadeless" ), 0 );

        // shadowing
        if ( shadowCamera != NULL )
        {
            // calculate and pass in shadow
            glm::mat4 shadowMatrix =
                shadowCamera->getProjectionMatrix() *
                shadowCamera->getViewMatrix() *
                m_modelMatrix;
            shadowMatrix = BIAS_MATRIX * shadowMatrix;
            glUniformMatrix4fv(
                glGetUniformLocation( program, "u_shadowMatrix" ),
                1, GL_FALSE, &shadowMatrix[0][0] );

            // pass in the shadow map
            glActiveTexture( GL_TEXTURE1 );
            glUniform1i( glGetUniformLocation( program, "u_shadowMap" ), 1 );
            glBindTexture( GL_TEXTURE_2D, lightData.shadowMap );
            glActiveTexture( GL_TEXTURE0 );

            // pass in the shadow caster
            glUniform1i(
                    glGetUniformLocation( program, "u_shadowCaster" ),
                    lightData.shadowCaster
            );
        }
        else
        {
            glUniform1i( glGetUniformLocation( program, "u_shadowing" ), 0 );
        }

        // pass in ambient light
        glm::vec3 ambientLight =
            renderSettings.getAmbientColour() *
            renderSettings.getAmbientStrength();
        glUniform3f(
            glGetUniformLocation( program, "u_ambientLight" ),
            ambientLight.r, ambientLight.g, ambientLight.b
        );

        // the number of lights
        glUniform1i(
            glGetUniformLocation( program, "u_lightCount" ),
            lightData.types.size()
        );
        if ( lightData.types.size() > 0 )
        {
            // the types of lights
            glUniform1iv(
                glGetUniformLocation( program, "u_lightType" ),
                lightData.types.size(),
                &lightData.types[0]
            );
            // the positions of lights
            glUniform3fv(
                glGetUniformLocation( program, "u_lightPos" ),
                lightData.types.size(),
                &lightData.positions[0]
            );
            // the rotations of lights
            glUniform3fv(
                glGetUniformLocation( program, "u_lightRot" ),
                lightData.types.size(),
                &lightData.rotations[0]
            );
            // the colours of lights
            glUniform3fv(
                glGetUniformLocation( program, "u_lightColour" ),
                lightData.types.size(),
                &lightData.colours[0]
            );
            // the attenuation of lights
            glUniform3fv(
                glGetUniformLocation( program, "u_lightAttenuation" ),
                lightData.types.size(),
                &lightData.attenuations[0]
            );
            // the arcs of lights
            glUniform2fv(
                glGetUniformLocation( program, "u_lightArc" ),
                lightData.types.size(),
                &lightData.arcs[0]
            );
            // the inverse states of light
            glUniform1iv(
                glGetUniformLocation( program, "u_lightInverse" ),
                lightData.types.size(),
                &lightData.inverses[0]
            );

            // form a list of the lights this mesh is ignoring
            std::vector<int> ignore;
            for ( std::vector<std::string>::const_iterator it =
                  lightData.names.begin();
                  it != lightData.names.end(); ++it )
            {
                if ( std::find(
                        m_ignoreLights.begin(),
                        m_ignoreLights.end(),
                        *it ) != m_ignoreLights.end() )
                {
                    ignore.push_back( 1 );
                }
                else
                {
                    ignore.push_back( 0 );
                }
            }
            glUniform1iv(
                glGetUniformLocation( program, "u_lightIgnore" ),
                lightData.types.size(),
                &ignore[0]
            );
        }
    }

    //--------------------------------PROPERTIES--------------------------------

    // specular property
    Specular* specular = m_material.specular;
    float shininess = 0.0f;
    glm::vec3 specularColour;
    if ( specular != NULL )
    {
        shininess = specular->getShininess();
        specularColour = specular->getColour();
        if ( specular->getMap() != NULL )
        {
            glActiveTexture( GL_TEXTURE2 );
            glUniform1i( glGetUniformLocation( program, "u_hasSpecMap" ), 1 );
            glUniform1i( glGetUniformLocation( program, "u_specMap" ), 2 );
            glBindTexture( GL_TEXTURE_2D, specular->getMap()->getId() );
            glActiveTexture( GL_TEXTURE0 );
        }
        else
        {
            glUniform1i( glGetUniformLocation( program, "u_hasSpecMap" ), 0 );
        }
    }
    glUniform1f(
        glGetUniformLocation( program, "u_shininess" ),
        shininess
    );
    glUniform3f(
        glGetUniformLocation( program, "u_specularColour" ),
        specularColour.r,
        specularColour.g,
        specularColour.b
    );
}

void Renderable::unsetShader()
{
    glUseProgram( 0 );
    glBindTexture( GL_TEXTURE_2D, 0 );
}

} // namespace omi
