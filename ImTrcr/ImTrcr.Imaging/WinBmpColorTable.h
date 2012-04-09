#pragma once

#include "Common.h"
#include "ArgbQuad.h"
#include <iostream>
#include <vector>

namespace ImTrcr {
namespace Imaging {

    //Represents a transformer from raw bitmap data to colors
    class WinBmpColorTable {
    public:
        //transforms raw bitmap data to color info
        ArgbQuad GetColor(byte* dataPtr) const;

        static WinBmpColorTable* FromStream(byte bitsPerPixel, unsigned long numberOfColors, std::istream& input);
    private:
        WinBmpColorTable(byte bitsPerPixel, const std::vector<ArgbQuad>& colorTable);
        std::vector<ArgbQuad> table;
        byte bitsPerPixel;
        bool indexed;
    };

}
}