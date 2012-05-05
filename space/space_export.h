#include <QtCore/qglobal.h>

#if defined BUILD_SPACE_LIBRARY
#  define SPACE_EXPORT Q_DECL_EXPORT
#else
#  define SPACE_EXPORT Q_DECL_IMPORT
#endif