#ifndef SPACE_CORE_EXPORT_H
#define SPACE_CORE_EXPORT_H

#include <QtCore/qglobal.h>

#if defined BUILD_SPACE_CORE_LIBRARY
#  define SPACE_CORE_EXPORT Q_DECL_EXPORT
#else
#  define SPACE_CORE_EXPORT Q_DECL_IMPORT
#endif

#endif // SPACE_CORE_EXPORT_H