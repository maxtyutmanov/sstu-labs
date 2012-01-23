#pragma once

#include <string>

namespace JustCompiler {
namespace CodeGeneration {

    class Variable {
    public:
        Variable(const std::wstring& name, bool isTmp = false)
            : name(name), isTmp(isTmp) {}

        std::wstring GetName() const {
            return name;
        }
    private:
        std::wstring name;
        bool isTmp;
    };

}
}