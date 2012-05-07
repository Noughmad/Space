#ifndef SPACE_STRING_H
#define SPACE_STRING_H

#include <string>
#include <QList>

#include "core_export.h"

template <class T> class QList;

namespace Space {
    typedef std::string String;
    typedef QList<std::string> StringList;
    
    StringList SPACE_CORE_EXPORT split(const Space::String& str);
};

uint qHash(const Space::String& str);

#endif // SPACE_STRING_H
