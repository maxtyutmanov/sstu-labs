#pragma once

#include <map>
#include <string>
#include "TokenTag.h"

namespace JustCompiler {
namespace LexicalAnalyzer {

    class LexemeToTagMapping {
    public:
        void AddPair(const std::wstring& lexeme, const TokenTag::Enum tokenTag);
        bool TryGetTokenTag(const std::wstring& lexeme, TokenTag::Enum& outTokenTag) const;
    private:
        std::map<std::wstring, TokenTag::Enum> mappingInternal;
    };

}
}