#pragma once

#define IN
#define OUT

#include <assert.h>

namespace ImTrcr {
namespace Imaging {

    //Represents one pixel value in RGBA color space
    struct RGBTriple {
        RGBTriple() {
            red = 0;
            green = 0;
            blue = 0;
        }

        RGBTriple(unsigned char alpha, unsigned char red, unsigned char green, unsigned char blue)
            : red(red), green(green), blue(blue) {}

        RGBTriple(unsigned char red, unsigned char green, unsigned char blue)
            : red(red), green(green), blue(blue) {}

        bool operator == (const RGBTriple& right) {
            return this->red == right.red && this->green == right.green && this->blue == right.blue;
        }

        bool operator != (const RGBTriple& right) {
            return !(*this == right);
        }

        unsigned char red;
        unsigned char green;
        unsigned char blue;
    };

    //NOTE: this has to be signed, otherwise some cycles in code would be broken!
    typedef signed int image_size_t;

}
}