#include "VisibilityCheckThread.hpp"

namespace omi {

namespace vis_check {

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

boost::mutex mutex;
bool kill = false;
bool ready = true;
bool sort = false;
std::vector<GLubyte>* buffer = NULL;
std::set<unsigned> visibleSet;

void sortVisible()
{
    util::thread::setCurrentPriority( 0 );

    while ( !kill )
    {
        // lock and get the state of the sort variable
        bool safe_sort = false;
        {
            boost::unique_lock<boost::mutex> lock( mutex );
            safe_sort = sort;
        }

        // check if we need sort the buffer
        if ( safe_sort )
        {
            // lock and update fields
            {
                boost::unique_lock<boost::mutex> lock( mutex );
                // exit if we've been given no data
                if ( buffer == NULL || buffer->empty() )
                {
                    return;
                }

                ready = false;
                sort = false;
            }

            // clear any previous work
            visibleSet.clear();

            // sort the buffer
            for ( unsigned i = 0; i < buffer->size(); ++i )
            {
                // build the colour key
                unsigned colour =  static_cast<unsigned>( ( *buffer )[ i ] );
                colour |= static_cast<unsigned>( ( *buffer )[ i + 1 ] ) << 8;
                colour |= static_cast<unsigned>( ( *buffer )[ i + 2] ) << 16;

                // add to the set of colours
                visibleSet.insert( colour );
            }

            // lock and update fields
            {
                boost::unique_lock<boost::mutex> lock( mutex );
                ready = true;
            }
        }
        else
        {
            util::time::sleep( 5 );
        }
    }
}

} // namespace vis_check

} // namespace omi
