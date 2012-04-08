#pragma once

#include "Common.h"
#include "ArgbQuad.h"
#include <iostream>
#include <vector>

namespace ImTrcr {
namespace Imaging {

    //represents a pallette used by windows BMP file
    class WinBmpColorTable {
    public:
        ArgbQuad GetColor(unsigned char* dataPtr);

        static WinBmpColorTable* FromStream(unsigned short bitsPerPixel, unsigned short numberOfColors, std::istream& input);
    private:
        WinBmpColorTable(unsigned short bitsPerPixel, const std::vector<ArgbQuad>& colorTable);

        std::vector<ArgbQuad> colorTable;
        unsigned short bitsPerPixel;

        bool indexed;
    };

}
}