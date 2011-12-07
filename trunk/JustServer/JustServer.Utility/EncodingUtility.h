#ifndef ENCODING_UTILITY_H
#define ENCODING_UTILITY_H

#include <string>

namespace JustServer {
namespace Utility {

    class EncodingUtility {
    public:
        static std::wstring Utf8ToWideChar(const std::string& utf8string);
    };

}
}

#endif