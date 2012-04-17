#pragma once

#include "ITracer.h"

namespace ImTrcr {
namespace Vectorization {

    //Implements vectorization using Potrace algorithm
    class PotraceTracer : public ITracer {
    public:
        virtual Imaging::VectorImage* Trace(const Imaging::RasterImage& rasterImage);
    };

}
}