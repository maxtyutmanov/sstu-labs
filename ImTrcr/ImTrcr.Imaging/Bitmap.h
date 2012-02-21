#pragma once

#include "Common.h"
#include <iostream>

namespace ImTrcr {
namespace Imaging {

    //Represents any raster image. Encapsulates logic that is common 
    //for all raster images regardless of format
    class Bitmap {
    public:
        RGBTriple GetPixel(image_size_t x, image_size_t y) const;
        void SetPixel(image_size_t x, image_size_t y, RGBTriple argb);

        //converts the image to the stream of bytes
        virtual void ToStream(std::ostream& output) const = 0;

        image_size_t GetWidth() const;
        image_size_t GetHeight() const;

        virtual ~Bitmap();
    protected:
        Bitmap(image_size_t width, image_size_t height, RGBTriple* pixelArray);
        void CheckCoordinates(image_size_t x, image_size_t y) const;

        image_size_t width;
        image_size_t height;
        RGBTriple* pixelArray;
    private:

        //there's no way you can copy bitmap! haha!
        Bitmap(const Bitmap& other);
        Bitmap& operator = (const Bitmap& other);
    };
}
}