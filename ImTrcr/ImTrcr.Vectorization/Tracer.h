#pragma once

#include "VectorImage.h"
#include <Bitmap.h>

namespace ImTrcr {
namespace Vectorization {

    class Tracer {
    public:
        VectorImage* Trace(const Imaging::Bitmap& bmp);
    };

}
}