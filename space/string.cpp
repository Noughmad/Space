#include "string.h"
#include <CEGUIString.h>

using namespace Space;

String::String() : QString()
{

}

String::String(const char* ch) : QString(ch)
{

}

String::String(const std::string& a) : QString(fromStdString(a))
{

}

String::String(const QString& qs): QString(qs)
{

}


String::operator QString() const
{
    return mid(0);
}

String::operator std::string() const
{
    return toStdString();
}

String::operator std::string()
{
    return toStdString();
}

String::operator CEGUI::String() const
{
    return CEGUI::String(toStdString());
}

String Space::operator+(const String& str, const char* ch)
{
    return String(str.mid(0) + ch);
}
