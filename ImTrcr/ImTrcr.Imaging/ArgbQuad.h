#pragma once

#include "Common.h"

namespace ImTrcr {
namespace Imaging {
    //Represents one pixel value in ARGB color space
    struct ArgbQuad {
        ArgbQuad() {
            alpha = 255;
            red = 0;
            green = 0;
            blue = 0;
        }

        ArgbQuad(unsigned char alpha, unsigned char red, unsigned char green, unsigned char blue)
            : alpha(alpha), red(red), green(green), blue(blue) {}

        ArgbQuad(unsigned char red, unsigned char green, unsigned char blue)
            : alpha(255), red(red), green(green), blue(blue) {}

        bool operator == (const ArgbQuad& right) {
            return this->alpha == right.alpha && this->red == right.red && this->green == right.green && this->blue == right.blue;
        }

        bool operator != (const ArgbQuad& right) {
            return !(*this == right);
        }

        byte red;
        byte green;
        byte blue;
        byte alpha;
    };
}
}