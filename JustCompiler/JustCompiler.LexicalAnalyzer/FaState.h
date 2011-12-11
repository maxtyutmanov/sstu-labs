#pragma once

#include "Global.h"

namespace JustCompiler {
namespace LexicalAnalyzer {

    class FaState {
    public:
        FaState(const string_type& name);

        string_type GetName() const;
    private:
        string_type name;
    };

}
}