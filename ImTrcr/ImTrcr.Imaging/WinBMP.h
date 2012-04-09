#pragma once

#include "RasterImage.h"
#include "ArgbQuad.h"
#include "WinBmpColorTable.h"
#include <string>
#include <vector>

namespace ImTrcr {
namespace Imaging {

    typedef unsigned short WORD;
    typedef unsigned long DWORD;
    typedef long LONG;

    #pragma pack(2) //it turns on 2 byte alignment
    typedef struct tagBITMAPFILEHEADER {
        WORD    bfType;
        DWORD   bfSize;
        WORD    bfReserved1;
        WORD    bfReserved2;
        DWORD   bfOffBits;
    } BITMAPFILEHEADER;
    #pragma pack()

    typedef struct tagBITMAPINFOHEADER {
        DWORD      biSize;
        LONG       biWidth;
        LONG       biHeight;
        WORD       biPlanes;
        WORD       biBitCount;
        DWORD      biCompression;
        DWORD      biSizeImage;
        LONG       biXPelsPerMeter;
        LONG       biYPelsPerMeter;
        DWORD      biClrUsed;
        DWORD      biClrImportant;
    } BITMAPINFOHEADER;

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