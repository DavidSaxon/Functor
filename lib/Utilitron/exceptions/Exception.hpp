#ifndef UTILITRON_EXCEPTIONS_EXCEPTION_H_
#   define UTILITRON_EXCEPTIONS_EXCEPTION_H_

#include <exception>
#include <iostream>
#include <sstream>

namespace util {

/***************************************************************************\
| Exceptions that extend from std::exceptions. All exceptions provide a     |
| getMessage() member function which will return the type of exception  and |
| the reason for the exception being thrown.                                |
\***************************************************************************/
namespace ex {

/************************************************************\
| An abstract base class which inherits from std::exception. |
\************************************************************/
class Exception : public std::exception {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Super constructor for Utilitron exceptions
    @param message the error message of the exception */
    Exception(const std::string& message) : m_errorMessage(message) {
    }

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~Exception() throw() {
    }

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** @return the error message of the exception */
    const char* what() const throw() {

        std::string message = info();

        // create a char array for the message
        char* rMessage = new char[message.length() + 1];
        // copy over the message
        for (unsigned i = 0; i < message.length(); ++i) {

            rMessage[i] = message[i];
        }
        // put the terminating character on the end
        rMessage[message.length()] = '\0';

        return rMessage;
    }

    /** @return the error message of the exception */
    std::string getMessage() const {

        return m_errorMessage;
    }

protected:

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** @return the name of the exception */
    virtual std::string name() const = 0;

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the error message
    std::string m_errorMessage;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** @return the exception name joint with the error message */
    std::string info() const {

        std::stringstream ss;
        ss << name() << ": " << m_errorMessage;

        return ss.str();
    }
};

} // namespace ex

} // namespace util

#endif
