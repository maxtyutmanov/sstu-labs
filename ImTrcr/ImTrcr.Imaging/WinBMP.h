#pragma once

#include "RasterImage.h"
#include "ArgbQuad.h"
#include "WinBmpColorTable.h"
#include <string>
#include <vector>

namespace ImTrcr {
namespace Imaging {

    //Device independent bitmap (DIB) - Windows bitmap format
    class WinBMP : public RasterImage {
    public:
        //inherited
        virtual ArgbQuad GetColor(image_size_t x, image_size_t y) const;
        //loads bitmap from specified stream
        static WinBMP FromStream(std::istream& input);

        virtual ~WinBMP();
    private:
        WinBMP(image_size_t width, image_size_t height, byte* bmpData, WinBmpColorTable* colorTable, byte bitsPerPixel);

        byte bitsPerPixel;
        byte* bmpData;
        WinBmpColorTable* colorTable;
    };

}
}