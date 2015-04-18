#ifndef UTILITRON_MACROUTIL_H_
#   define UTILITRON_MACROUTIL_H_

/** Use this macro in the private section of a class to disallow all forms of
construction */
#define DISALLOW_CONSTRUCTION(TypeName) \
    TypeName();                            \
    TypeName(const TypeName&);             \
    void operator=(const TypeName&)

/** Use this macro in the private section of a class to disallow
the default copy constructor */
#define DISALLOW_DEFAULT_COPY(TypeName) \
    TypeName(const TypeName&)

/** Use this macro in the private section of a class to disallow
copying and assignment */
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);             \
    void operator=(const TypeName&)

#endif
