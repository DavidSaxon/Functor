#ifndef OMICRON_RESOURCE_TYPE_RESOURCE_H_
#   define OMICRON_RESOURCE_TYPE_RESOURCE_H_

#include <GL/glew.h>
#include <iostream>
#include <SFML/OpenGL.hpp>

#include "lib/Utilitron/MacroUtil.hpp"

#include "src/omicron/resource/loader/Loaders.hpp"
#include "src/override/ResourceGroups.hpp"

namespace omi {

/**********************************************************************\
| Abstract base class for all resources. Defines loading and releasing |
| functions, and resource group access.                                |
\**********************************************************************/
class Resource {
private:

    //--------------------------------------------------------------------------
    //                                RESTRICTIONS
    //--------------------------------------------------------------------------

    DISALLOW_COPY_AND_ASSIGN(Resource);

public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Super constructor
    @param resourceGroup the resource group the resource is within */
    Resource(resource_group::ResourceGroup resourceGroup) :
        m_loaded       (false),
        m_resourceGroup(resourceGroup) {
    }

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~Resource() {
    }

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Loads the resource */
    virtual void load() = 0;

    /** releases the resource */
    virtual void release() = 0;

    /** @return the resource group of the resource */
    resource_group::ResourceGroup getGroup() const {

        return m_resourceGroup;
    }

    /** @return if the resource has been loaded */
    bool isLoaded() const {

        return m_loaded;
    }

protected:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // true once the resource has been loaded
    bool m_loaded;
    // the resource group the resource is within
    resource_group::ResourceGroup m_resourceGroup;
};

} // namespace omi

#endif