#include "FaState.h"

namespace JustCompiler {
namespace LexicalAnalyzer {

    FaState::FaState(const string_type& name) {
        this->name = name;
    }

    string_type FaState::GetName() const {
        return name;
    }

}
}