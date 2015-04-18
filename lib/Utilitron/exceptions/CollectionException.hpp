#ifndef UTILITRON_EXCEPTIONS_COLLECTIONEXCEPTIONS_H_
#   define UTILITRON_EXCEPTIONS_COLLECTIONEXCEPTIONS_H_

#include "Exception.hpp"

namespace util {

namespace ex {

/****************************************************\
| Abstract base class for all collection exceptions. |
\****************************************************/
class CollectionException : public Exception {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Super constructor for collection exceptions
    @param message the error message of the exception */
    CollectionException(const std::string& message) : Exception(message) {
    }
};

/********************************************\
| Warns that a given index is out of bounds. |
\********************************************/
class IndexOutOfBoundsException : public CollectionException {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new index out of bounds exception
    @param message the error message */
    IndexOutOfBoundsException(const std::string& message) :
        CollectionException(message) {
    }

private:

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    std::string name() const {

        return "INDEX OUT OF BOUNDS EXCEPTION";
    }
};

/****************************************************\
| Warns that an item already exists in a collection. |
\****************************************************/
class ItemAlreadyExistsException : public CollectionException {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates an item already exists exception
    @param message the error message */
    ItemAlreadyExistsException(const std::string& message) :
        CollectionException(message) {        
    }

private:

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    std::string name() const {

        return "ITEM ALREADY EXIST EXCEPTION";
    }

};

} // namespace ex

} // namespace util

#endif
