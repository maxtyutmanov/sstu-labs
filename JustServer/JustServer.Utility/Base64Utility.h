#ifndef BASE_64_UTILITY_H
#define BASE_64_UTILITY_H

#include <string>

namespace JustServer {
namespace Utility {

    class Base64Utility {
    public:
        static bool TryDecodeBase64(std::string encoded, std::string& decoded);
    };

}
}

#endif