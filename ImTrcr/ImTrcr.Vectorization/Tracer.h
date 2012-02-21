#pragma once

#include "SvgImage.h"
#include <Bitmap.h>

namespace ImTrcr {
namespace Vectorization {

    class Tracer {
    public:
        SvgImage Trace(const Imaging::Bitmap& bmp);
    };

}
}