#pragma once

#include "Bitmap.h"
#include <string>
#include <vector>

namespace ImTrcr {
namespace Imaging {

    //Device independent bitmap (DIB) - Windows bitmap format
    class WinBMP : public Bitmap {
    public:
        //initializes an empty bitmap with specified width, height and color depth (bits per pixel)
        WinBMP(image_size_t width, image_size_t height, unsigned short colorDepth = 24);
        unsigned short GetColorDepth() const;
        //inherited
        virtual void ToStream(std::ostream& output) const;

        //creates a deep copy of the bitmap
        WinBMP Clone() const;

        //loads bitmap from specified path in file system
        static WinBMP FromFile(const std::wstring& path);
        //loads bitmap from specified stream
        static WinBMP FromStream(std::istream& input);
    private:
        WinBMP(image_size_t width, image_size_t height, RGBTriple* pixelArray, unsigned short colorDepth = 24);

        //Creates pixel array with default RGB values for each pixel
        static RGBTriple* CreateDefaultPixelArray(image_size_t width, image_size_t height);

        //Converts data read from BMP file to array of RGB triples
        static RGBTriple* ConvertBmpDataToRGBBuffer(unsigned char* data, image_size_t width, image_size_t height, unsigned short bytesPerPixel);
        //Converts array of pixels (RGB triples) to array of bytes ready for saving to file or other stream
        unsigned char* ConvertRGBBufferToBmpData(unsigned long *resultLength) const;

        //number of bits per pixel
        unsigned short colorDepth;
    };

}
}