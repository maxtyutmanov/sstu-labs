#pragma once

#include "ISvgSerializer.h"

namespace ImTrcr {
namespace Imaging {

    class SvgSerializer : public ISvgSerializer {
    public:
        virtual TiXmlDocument* Serialize(const Imaging::VectorImage& vectorImage) const;
    };

}
}