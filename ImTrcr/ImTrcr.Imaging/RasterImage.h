#pragma once

#include "Common.h"
#include "ArgbQuad.h"
#include <iostream>

namespace ImTrcr {
namespace Imaging {

    //Represents any raster image. Encapsulates logic that is common 
    //for all raster images regardless of format
    class RasterImage {
    public:
        //gets the color of specified pixel
        ArgbQuad GetColor(image_size_t x, image_size_t y) const;
        //sets the color of specified pixel
        void SetColor(image_size_t x, image_size_t y, ArgbQuad argb);

        image_size_t GetWidth() const;
        image_size_t GetHeight() const;

        //converts the image to the stream of bytes
        virtual void ToStream(std::ostream& output) const = 0;

        virtual ~RasterImage();
    protected:
        RasterImage(image_size_t width, image_size_t height, ArgbQuad* pixelArray);
        void CheckCoordinates(image_size_t x, image_size_t y) const;

        image_size_t width;
        image_size_t height;
        ArgbQuad* pixelArray;
    private:

        //there's no way you can copy bitmap!
        RasterImage(const RasterImage& other);
        RasterImage& operator = (const RasterImage& other);
    };
}
}