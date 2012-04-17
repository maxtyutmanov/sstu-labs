#pragma once

#define IN
#define OUT

namespace ImTrcr {
namespace Imaging {

    //NOTE: this has to be signed, otherwise some cycles in code would be broken!
    typedef signed int image_size_t;

    #ifndef byte
    typedef unsigned char byte;
    #endif
}
}