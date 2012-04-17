#pragma once

#include "Primitive.h"
#include <vector>

namespace ImTrcr {
namespace Imaging {

    //Represents an image as a set of geometric primitives
    class VectorImage {
    public:
        void AddPrimitive(Primitive* p);

        const std::vector<Primitive *>& GetPrimitives();
    private:
        std::vector<Primitive*> primitives;
    };

}
}