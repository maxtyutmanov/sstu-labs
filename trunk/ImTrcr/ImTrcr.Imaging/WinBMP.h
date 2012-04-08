#pragma once

#include "RasterImage.h"
#include "ArgbQuad.h"
#include <string>
#include <vector>

namespace ImTrcr {
namespace Imaging {

    //Device independent bitmap (DIB) - Windows bitmap format
    class WinBMP : public RasterImage {
    public:
        //initializes an empty bitmap with specified width, height and color depth (bits per pixel)
        WinBMP(image_size_t width, image_size_t height, unsigned short colorDepth);

        //inherited
        virtual void ToStream(std::ostream& output) const;

        //creates a deep copy of the bitmap
        WinBMP Clone() const;

        //loads bitmap from specified path in file system
        static WinBMP FromFile(const std::wstring& path);
        //loads bitmap from specified stream
        static WinBMP FromStream(std::istream& input);
    private:
        WinBMP(image_size_t width, image_size_t height, ArgbQuad* pixelArray, unsigned short colorDepth = 24);
        WinBMP(image_size_t width, image_size_t height, unsigned char* bmpData, ArgbQuad* colorTable, unsigned short colorDepth = 8);

        //Creates pixel array with default RGB values for each pixel
        static ArgbQuad* CreateDefaultPixelArray(image_size_t width, image_size_t height);

        //Converts data read from BMP file to array of RGB triples
        static ArgbQuad* ConvertBmpDataToRGBBuffer(unsigned char* data, image_size_t width, image_size_t height, unsigned short bytesPerPixel);
        //Converts array of pixels (RGB triples) to array of bytes ready for saving to file or other stream
        unsigned char* ConvertRGBBufferToBmpData(unsigned long *resultLength) const;

        bool UsesColorTable() const;

        //private getters and setters

        void SetColorDepth(unsigned short colorDepth);

        //end of private getters and setters

        //number of bits per pixel
        unsigned short colorDepth;
        ArgbQuad* colorTable;
    };

}
}