#ifndef UTF8_H
    #define UTF8_H

#include <string>

//
//  UTF8
//
class UTF8
{
    // Helper member function
    static unsigned char MakeByte(char Ch1, char Ch2);

public:
    // Public interface
    static std::string DecodeFrom(const char* Source);
    static std::string EncodeTo(const char* Source);
};

#endif

