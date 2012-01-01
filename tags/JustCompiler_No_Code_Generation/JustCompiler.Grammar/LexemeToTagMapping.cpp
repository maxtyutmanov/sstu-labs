#include "LexemeToTagMapping.h"

using namespace std;

namespace JustCompiler {
namespace LexicalAnalyzer {

    void LexemeToTagMapping::AddPair(const wstring& lexeme, const TokenTag::Enum tokenTag) {
        mappingInternal[lexeme] = tokenTag;
    }

    bool LexemeToTagMapping::TryGetTokenTag(const wstring& lexeme, TokenTag::Enum& outTokenTag) const {
        map<wstring, TokenTag::Enum>::const_iterator foundIt = mappingInternal.find(lexeme);

        if (foundIt != mappingInternal.end()) {
            outTokenTag = foundIt->second;
            return true;
        }
        else {
            return false;
        }
    }

}
}