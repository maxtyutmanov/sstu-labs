#include "RasterImage.h"
#include "PointOutOfBitmapException.h"

using namespace std;

namespace ImTrcr {
namespace Imaging {

    ArgbQuad RasterImage::GetColor(image_size_t x, image_size_t y) const {
        CheckCoordinates(x, y);

        return pixelArray[y * width + x];
    }

    void RasterImage::SetColor(image_size_t x, image_size_t y, ArgbQuad argb) {
        CheckCoordinates(x, y);

        pixelArray[y * width + x] = argb;
    }

    image_size_t RasterImage::GetWidth() const {
        return width;
    }

    image_size_t RasterImage::GetHeight() const {
        return height;
    }

    RasterImage::~RasterImage() {
        if (pixelArray != NULL) {
            delete[] pixelArray;
        }
    }

    RasterImage::RasterImage(image_size_t width, image_size_t height, ArgbQuad* pixelArray) {
        if (NULL == pixelArray) {
            throw logic_error("Pixel array of bitmap cannot be NULL");
        }

        if (width <= 0) {
            delete[] pixelArray;
            throw logic_error("Width of bitmap must be positive integer");
        }

        if (height <= 0) {
            delete[] pixelArray;
            throw logic_error("Height of bitmap must be positive integer");
        }

        this->width = width;
        this->height = height;
        this->pixelArray = pixelArray;
    }

    void RasterImage::CheckCoordinates(image_size_t x, image_size_t y) const {
        if (x < 0 || x >= width ||
            y < 0 || y >= height) {

            throw PointOutOfBitmapException(x, y);
        }
    }
}
}