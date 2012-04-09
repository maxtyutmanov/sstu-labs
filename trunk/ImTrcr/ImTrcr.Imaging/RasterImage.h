#pragma once

#include "Common.h"
#include "ArgbQuad.h"
#include <iostream>
#include <boost/noncopyable.hpp>

namespace ImTrcr {
namespace Imaging {

    //Represents any raster image. The objects of this
    //type cannot be copied
    class RasterImage : public boost::noncopyable {
    public:
        //gets the color of specified pixel
        virtual ArgbQuad GetColor(image_size_t x, image_size_t y) const = 0;

        image_size_t GetWidth() const;
        image_size_t GetHeight() const;

        virtual ~RasterImage() {};
    protected:
        RasterImage(image_size_t width, image_size_t height);
        void CheckCoordinates(image_size_t x, image_size_t y) const;
    private:
        image_size_t width;
        image_size_t height;
    };
}
}