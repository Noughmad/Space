#ifndef SPACE_STRING_H
#define SPACE_STRING_H

#include <QString>

namespace CEGUI {
class String;
}


namespace Space {

class String : public QString
{
public:
    String();
    String(const char* ch);
    String(const std::string& a);
    String(const QString& qs);
    
    operator QString() const;
    operator std::string() const;
    operator std::string();
    operator CEGUI::String() const;
};

String operator+(const String& str, const char* ch);

};

#endif // SPACE_STRING_H
