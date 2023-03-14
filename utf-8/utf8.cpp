#include "utf8.h"

#include <cstring>
using namespace std;

//
//  UTF8
//
string UTF8::DecodeFrom(const char* Source)
{
    string final_;

    unsigned int ch_;
    unsigned char z_, y_, x_, w_, v_, u_;

    size_t len = strlen(Source);

    for (size_t i = 0; i < len; ++i)
    {
        ch_ = (unsigned short)Source[i];

        if (ch_ != '=')
        {
            final_ += (char)ch_;
            continue;
        }

        if (i >= len - 2) break;                 // something is wrong

        z_ = MakeByte(Source[i+1], Source[i+2]);

        if (z_ < 127)
        {
            final_ += (char)z_;
            i = i + 2;
        }
        else if (z_ >= 192 && z_ <= 223)
        {
            // character is two bytes
            if (i >= len - 5) break;             // something is wrong

            y_ = MakeByte(Source[i+4], Source[i+5]);

            final_ += (char)( (z_-192)*64 + (y_-128) );
            i = i + 5;
        }
        else if (z_ >= 224 && z_ <= 239)
        {
            // character is three bytes
            if (i >= len - 8) break;             // something is wrong

            y_ = MakeByte(Source[i+4], Source[i+5]);
            x_ = MakeByte(Source[i+7], Source[i+8]);

            final_ += (char)( (z_-224)*4096 + (y_-128)*64 + (x_-128) );
            i = i + 8;
        }
        else if (z_ >= 240 && z_ <= 247)
        {
            // character is four bytes
            if (i >= len - 11) break;            // something is wrong

            y_ = MakeByte(Source[i+4] , Source[i+5] );
            x_ = MakeByte(Source[i+7] , Source[i+8] );
            w_ = MakeByte(Source[i+10], Source[i+11]);

            final_ += (char)( (z_-240)*262144 + (y_-128)*4096 + (x_-128)*64 + (w_-128) );
            i = i + 11;
        }
        else if (z_ >= 248 && z_ <= 251)
        {
            // character is four bytes
            if (i >= len - 14) break;            // something is wrong

            y_ = MakeByte(Source[i+4] , Source[i+5] );
            x_ = MakeByte(Source[i+7] , Source[i+8] );
            w_ = MakeByte(Source[i+10], Source[i+11]);
            v_ = MakeByte(Source[i+13], Source[i+14]);

            final_ += (char)( (z_-248)*16777216 + (y_-128)*262144 + (x_-128)*4096 + (w_-128)*64 + (v_-128) );
            i = i + 14;
        }
        else if (z_ >= 252 && z_ <= 253)
        {
            // character is four bytes
            if (i >= len - 17) break;            // something is wrong

            y_ = MakeByte(Source[i+4] , Source[i+5] );
            x_ = MakeByte(Source[i+7] , Source[i+8] );
            w_ = MakeByte(Source[i+10], Source[i+11]);
            v_ = MakeByte(Source[i+13], Source[i+14]);
            u_ = MakeByte(Source[i+16], Source[i+17]);

            final_ += (char)( (z_-252)*1073741824 + (y_-128)*16777216 + (x_-128)*262144 + (w_-128)*4096 + (v_-128)*64 + (u_-128) );
            i = i + 17;
        }

    }
    return final_;
}

string UTF8::EncodeTo(const char* Source)
{
    char buffer_[64];
    string final_;

    unsigned int ch_;
    unsigned char bt1_, bt2_, bt3_, bt4_, bt5_, bt6_;

    size_t len = strlen(Source);

    for (size_t i = 0; i < len; ++i)
    {
        ch_ = (unsigned short)Source[i];

        if (ch_ == '=')
        {
            sprintf(buffer_, "=%02X", ch_);
            final_ = buffer_;
        }
        else if (ch_ < 128)
        {
            final_ += Source[i];
        }
        else if (ch_ <= 2047)
        {
            bt1_ = (unsigned char)(192 + (ch_ / 64));
            bt2_ = (unsigned char)(128 + (ch_ % 64));

            sprintf(buffer_,"=%02X=%02X", bt1_, bt2_);
            final_ = buffer_;
        }
        else if (ch_ <= 65535)
        {
            bt1_ = (unsigned char)(224 + ( ch_ / 4096));
            bt2_ = (unsigned char)(128 + ((ch_ / 64) % 64));
            bt3_ = (unsigned char)(128 + ( ch_ % 64));

            sprintf(buffer_,"=%02X=%02X=%02X", bt1_, bt2_, bt3_);
            final_ = buffer_;
        }
        else if (ch_ <= 2097151)
        {
            bt1_ = (unsigned char)(240 + ( ch_ / 262144));
            bt2_ = (unsigned char)(128 + ((ch_ / 4096) % 64));
            bt3_ = (unsigned char)(128 + ((ch_ / 64) % 64));
            bt4_ = (unsigned char)(128 + ( ch_ % 64));

            sprintf(buffer_,"=%02X=%02X=%02X=%02X", bt1_, bt2_, bt3_, bt4_);
            final_ = buffer_;
        }
        else if (ch_ <= 67108863)
        {
            bt1_ = (unsigned char)(248 + ( ch_ / 16777216));
            bt2_ = (unsigned char)(128 + ((ch_ / 262144) % 64));
            bt3_ = (unsigned char)(128 + ((ch_ / 4096) % 64));
            bt4_ = (unsigned char)(128 + ((ch_ / 64) % 64));
            bt5_ = (unsigned char)(128 + ( ch_ % 64));

            sprintf(buffer_,"=%02X=%02X=%02X=%02X=%02X", bt1_, bt2_, bt3_, bt4_, bt5_);
            final_ = buffer_;
        }
        else if (ch_ <= 2147483647)
        {
            bt1_ = (unsigned char)(252 + ( ch_ / 1073741824));
            bt2_ = (unsigned char)(128 + ((ch_ / 16777216) % 64));
            bt3_ = (unsigned char)(128 + ((ch_ / 262144) % 64));
            bt4_ = (unsigned char)(128 + ((ch_ / 4096) % 64));
            bt5_ = (unsigned char)(128 + ((ch_ / 64) % 64));
            bt6_ = (unsigned char)(128 + ( ch_ % 64));

            sprintf(buffer_,"=%02X=%02X=%02X=%02X=%02X=%02X", bt1_, bt2_, bt3_, bt4_, bt5_, bt6_);
            final_ = buffer_;
        }

    }
    return final_;
}

unsigned char UTF8::MakeByte(char Ch1, char Ch2)
{
    unsigned char bt1_ = 0, bt2_ = 0;

    switch (Ch2)
    {
        case '0' : bt2_ = 0x00; break;
        case '1' : bt2_ = 0x01; break;
        case '2' : bt2_ = 0x02; break;
        case '3' : bt2_ = 0x03; break;
        case '4' : bt2_ = 0x04; break;
        case '5' : bt2_ = 0x05; break;
        case '6' : bt2_ = 0x06; break;
        case '7' : bt2_ = 0x07; break;
        case '8' : bt2_ = 0x08; break;
        case '9' : bt2_ = 0x09; break;
        case 'A' : bt2_ = 0x0A; break;
        case 'B' : bt2_ = 0x0B; break;
        case 'C' : bt2_ = 0x0C; break;
        case 'D' : bt2_ = 0x0D; break;
        case 'E' : bt2_ = 0x0E; break;
        case 'F' : bt2_ = 0x0F; break;
    }

    switch (Ch1)
    {
        case '0' : bt1_ = 0x00; break;
        case '1' : bt1_ = 0x10; break;
        case '2' : bt1_ = 0x20; break;
        case '3' : bt1_ = 0x30; break;
        case '4' : bt1_ = 0x40; break;
        case '5' : bt1_ = 0x50; break;
        case '6' : bt1_ = 0x60; break;
        case '7' : bt1_ = 0x70; break;
        case '8' : bt1_ = 0x80; break;
        case '9' : bt1_ = 0x90; break;
        case 'A' : bt1_ = 0xA0; break;
        case 'B' : bt1_ = 0xB0; break;
        case 'C' : bt1_ = 0xC0; break;
        case 'D' : bt1_ = 0xD0; break;
        case 'E' : bt1_ = 0xE0; break;
        case 'F' : bt1_ = 0xF0; break;
    }

    unsigned char byte = bt2_ | bt1_;
    return byte;
}

