#pragma once

#include <memory>
#include <Lexer.h>
#include "LexemeToTagMapping.h"
using std::auto_ptr;

namespace JustCompiler {
namespace LexicalAnalyzer {

    class MyGrammar {
    public:
        static boost::shared_ptr<LexemeToTagMapping> GetKeywordsMapping();
        static boost::shared_ptr<LexemeToTagMapping> GetStandardFuncMapping();
        static boost::shared_ptr<LexemeToTagMapping> GetSingleCharTokensMapping();

        static auto_ptr<Lexer> CreateLexer();

        static bool ValidateCharsetInIdentifier(wchar_t ch);
    };

}
}