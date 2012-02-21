#include "Bitmap.h"
#include "PointOutOfBitmapException.h"

using namespace std;

namespace ImTrcr {
namespace Imaging {

    RGBTriple Bitmap::GetPixel(image_size_t x, image_size_t y) const {
        CheckCoordinates(x, y);

        return pixelArray[y * width + x];
    }

    void Bitmap::SetPixel(image_size_t x, image_size_t y, RGBTriple argb) {
        CheckCoordinates(x, y);

        pixelArray[y * width + x] = argb;
    }

    image_size_t Bitmap::GetWidth() const {
        return width;
    }

    image_size_t Bitmap::GetHeight() const {
        return height;
    }

    Bitmap::~Bitmap() {
        if (pixelArray != NULL) {
            delete[] pixelArray;
        }
    }

    Bitmap::Bitmap(image_size_t width, image_size_t height, RGBTriple* pixelArray) {
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

    void Bitmap::CheckCoordinates(image_size_t x, image_size_t y) const {
        if (x < 0 || x >= width ||
            y < 0 || y >= height) {

            throw PointOutOfBitmapException(x, y);
        }
    }
}
}