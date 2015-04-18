#ifndef OMICRON_RENDERING_SHADING_ANIMATION_H_
#   define OMICRON_RENDERING_SHADING_ANIMATION_H_

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <vector>

#include "lib/Utilitron/TimeUtil.hpp"

#include "Texture.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                TYPE DEFINITIONS
//------------------------------------------------------------------------------

typedef std::vector<GLuint> t_TextureList;

/************************************************************************************\
| An animation is a subclass of a texture that can change the texture based on time. |
\************************************************************************************/
class Animation : public Texture {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /** Creates an empty animation */
    Animation();

    /** Creates a new animation with the given list of OpenGL texture pointers
    @param textures the list of pointers to OpenGL textures
    @param frameRate the animation playback speed
    @param repeat if the animation repeats */
    Animation( const t_TextureList& textures, unsigned frameRate, bool repeat );

    /** Creates a copy of the given animation
    @param other the animation to copy from */
    Animation( const Animation& other );

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    const Animation& operator=( const Animation& other );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void update();

    /** #Override */
    tex::Type getType() const;

    /** @return the length of the animation */
    unsigned getLength() const;

    /** Sets the current frame of the animation
    @param frame the new current frame of the animation (between 1 and animation
    length inclusive)*/
    void setFrame( unsigned frame );

    /** Pauses playback of the animation */
    void pause();

    /** Resumes playback of the animation if it is currently paused */
    void resume();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the list of OpenGL pointers to textures
    t_TextureList m_textures;

    // the framerate of the animation
    unsigned m_frameRate;
    // the frame length of the animation in ms
    util::int64 m_frameLength;
    // the current frame of the animation
    unsigned m_frame;

    // is true if the animation is paused
    bool m_paused;
    // is true if the animation should repeat
    bool m_repeat;
    // is true if the animation has ended
    bool m_ended;

    // the time the last frame begin
    util::int64 m_lastFrameTime;
    // the accumulated time from the last frame
    util::int64 m_accumTime;
};

} // namespace omi

#endif
