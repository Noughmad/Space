#include "string.h"
#include <QStringList>

using namespace Space;

StringList split(const String& str)
{
    StringList list;
    foreach (const QString qs, QString::fromStdString(str).split('/'))
    {
        list << qs.toStdString();
    }
    return list;
}

uint qHash(const String& str)
{
    return qHash(str.c_str());
}



/*

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

*/
