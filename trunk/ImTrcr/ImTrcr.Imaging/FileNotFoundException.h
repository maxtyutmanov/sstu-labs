#pragma once

#include <stdexcept>
#include <string>

namespace ImTrcr {
namespace Imaging {

    class FileNotFoundException : public std::runtime_error {
    public:
        FileNotFoundException(const std::wstring& filePath)
            : std::runtime_error("File with specified path cannot be found"), filePath(filePath) {}

        std::wstring GetFilePath() const {
            return filePath;
        }
    private:
        std::wstring filePath;
    };

}
}