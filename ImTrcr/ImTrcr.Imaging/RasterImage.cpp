#include "RasterImage.h"
#include "PointOutOfBitmapException.h"

using namespace std;

namespace ImTrcr {
namespace Imaging {

    image_size_t RasterImage::GetWidth() const {
        return width;
    }

    image_size_t RasterImage::GetHeight() const {
        return height;
    }

    RasterImage::RasterImage(image_size_t width, image_size_t height) {
        if (width <= 0) {
            throw logic_error("Width of bitmap must be positive integer");
        }

        if (height <= 0) {
            throw logic_error("Height of bitmap must be positive integer");
        }

        this->width = width;
        this->height = height;
    }

    void RasterImage::CheckCoordinates(image_size_t x, image_size_t y) const {
        if (x < 0 || x >= width ||
            y < 0 || y >= height) {

            throw PointOutOfBitmapException(x, y);
        }
    }
}
}