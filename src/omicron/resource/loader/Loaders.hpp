#ifndef OMICRON_RESOURCE_LOADER_LOADERS_H_
#   define OMICRON_RESOURCE_LOADER_LOADERS_H_

#include <boost/thread.hpp>
#include <fstream>
#include <GL/glew.h>
#include <iostream>
#include <IL/il.h>
#include <map>
#include <memory>
#include <SFML/OpenGL.hpp>
#include <sstream>

#include "lib/Utilitron/FileUtil.hpp"
#include "lib/Utilitron/StringUtil.hpp"

#include "src/omicron/rendering/object_data/Geometry.hpp"
#include "src/omicron/rendering/shading/Animation.hpp"
#include "src/omicron/rendering/shading/Font.hpp"
#include "src/omicron/rendering/shading/Material.hpp"
#include "src/omicron/rendering/shading/Shader.hpp"
#include "src/omicron/rendering/shading/Texture.hpp"

namespace omi {

/***********************************************\
| Functions used for loading data into Omicron. |
\***********************************************/
namespace loader {

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

//---------------------------------FONT LOADERS---------------------------------

/** Loads a front from a file
@param the free font library object
@param filePath the file path to the font */
Font* loadFontFromFile(
    FT_Library* freeType,
    const std::string& filePath );

//--------------------------------SHADER LOADERS--------------------------------

/** Loads a shader from seperate file paths for each shader
@param vertexPath the path to the vertex shader
@param fragmentPath the path to the fragment shader */
Shader loadShaderFromFiles(
        const std::string& vertexPath,
        const std::string& fragmentPath);

//-------------------------------TEXTURE LOADERS--------------------------------

/** Loads a texture from an image file
@param filePath the path to the image
@param clamp whether to clamp the texture to the edge
@param showPixels whether to interpolate the texture when scaling
@return the loaded texture */
Texture* textureFromImage(
    const std::string& filePath, bool clamp, bool showPixels );

/** Loads an animation from an image sequence
@param filePath the path of the sequence (omitting the frame number)
@param frameRate the playback speed of the animation
@param repeat if the animation should repeat
@param begin the beginning frame of the animation
@param end the ending frame of the animation
@param clamp whether to clamp the texture to the edge
@param showPixels whether to interpolate the texture when scaling*/
Texture* animationFromImage(
    const std::string& filePath, unsigned frameRate,
    bool repeat, unsigned begin, unsigned end, bool clamp, bool showPixels );

//-------------------------------GEOMETRY LOADERS-------------------------------

/** Loads geometry data from a wavefront file
@param filePath the path to the file to load the data from
@return the loaded geometry data */
Geometry* geoFromWavefront(const std::string& filePath);

/** Loads a list of geometry from a key frame set of wavefront files
@param path the path to keyframe file
@param geoMap a map from animation names to their respective lists of geometry
@param frameMap a map from animation to number of frames between each key
@param defaultAni returns the name of the default animation */
void geoFromKeyFrameWavefront(
        const std::string& path,
        std::map<std::string, std::vector<Geometry*>>& geoMap,
        std::map<std::string, std::vector<unsigned>>&  frameMap,
        std::string& defaultAni );

} // namespace loader

} // namespace omi

#endif
