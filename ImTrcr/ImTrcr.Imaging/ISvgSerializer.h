#pragma once

#include "VectorImage.h"
#include <tinyxml.h>

namespace ImTrcr {
namespace Imaging {

    class ISvgSerializer {
    public:
        virtual TiXmlDocument* Serialize(const Imaging::VectorImage& vectorImage) const = 0;
    };

}
}