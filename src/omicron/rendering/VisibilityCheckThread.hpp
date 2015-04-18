#ifndef OMICRON_RENDERING_VISIBILITYCHECKTHREAD_HPP_
#   define OMICRON_RENDERING_VISIBILITYCHECKTHREAD_HPP_

#include <iostream>
#include <set>
#include <vector>
#include <boost/thread/mutex.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include "lib/Utilitron/ThreadUtil.hpp"
#include "lib/Utilitron/TimeUtil.hpp"

namespace omi {

namespace vis_check {

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

// the mutex to ensure thread safety
extern boost::mutex mutex;

// true to kill the thread
extern bool kill;
// if the function is available to run
extern bool ready;
// set to run sorting
extern bool sort;
// a pointer to the buffer to sort
extern std::vector<GLubyte>* buffer;
// the set of colour keys of renderables that are visible
extern std::set<unsigned> visibleSet;

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/** Does the job of sorting which elements are visible into a set */
void sortVisible();

} // namespace vis_check

} // namespace omi

#endif
