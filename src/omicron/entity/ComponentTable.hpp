#ifndef OMICRON_ENTITY_COMPONENTTABLE_H_
#   define OMICRON_ENTITY_COMPONENTTABLE_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "lib/Utilitron/MacroUtil.hpp"
#include "lib/Utilitron/exceptions/CollectionException.hpp"

#include "src/omicron/component/Component.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                    TYPEDEF
//------------------------------------------------------------------------------

typedef std::map<std::string, std::unique_ptr<Component>> t_ComponentMap;

/************************************************************************\
| A component table contains a set of generic components mapped by their |
| unique identifiers.                                                    |
\************************************************************************/
class ComponentTable {
public:

    //--------------------------------------------------------------------------
    //                                RESTRICTIONS
    //--------------------------------------------------------------------------

    DISALLOW_COPY_AND_ASSIGN(ComponentTable);

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    //! #Hidden
    //! list of components that have been added that have not been sorted by the
    //! Logic Manager yet
    std::vector<Component*> newComponents;
    //! #Hidden
    //! List of components to be removed
    std::vector<Component*> removeComponents;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Create a new Component Table */
    ComponentTable();

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~ComponentTable();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Checks if the table contains a component with the given type
    @param id the identifier of the component to check for
    @return if the component is contained with the table */
    bool contains(const std::string& id);

    /** Get a the component with the given id if it exists within the table.
    Otherwise return null
    @param id the identifier of the component to get
    @return the component if it was found else null */
    Component* get(const std::string& id);

    /** Adds a component to the table
    #NOTE: the component table will take ownership of the component pointer
    @param component the pointer to the component */
    void add(Component* component);

    /** Removes the component with the given id from the able
    @param id the identifier of the component to remove
    @return if a component was successfully removed from the table */
    bool remove(const std::string& id);

    /** Copies all the components in the component table to the given list
    @param list the list to copy them to */
    void copyToList(std::vector<Component*>& list);

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the map from component ids to components
    t_ComponentMap m_components;
};

} // namespace omi

#endif
