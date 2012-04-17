#pragma once

#include <VectorImage.h>
#include <RasterImage.h>

namespace ImTrcr {
namespace Vectorization {

    //Encapsulates the vectorization logic
    class ITracer {
    public:
        virtual Imaging::VectorImage* Trace(const Imaging::RasterImage& rasterImage) = 0;
    };

}
}