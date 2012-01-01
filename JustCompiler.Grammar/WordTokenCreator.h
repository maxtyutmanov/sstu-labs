#pragma once

#include "Global.h"
#include "TokenCreator.h"
#include "CharValidationRule.h"
#include "LexemeToTagMapping.h"
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace LexicalAnalyzer {
namespace TokenCreators {

    //Creates tokens for keywords, standard functions and identifiers
    class WordTokenCreator : public TokenCreator {
    public:
        WordTokenCreator(
            boost::shared_ptr<LexemeToTagMapping> pKeywordsMapping, 
            boost::shared_ptr<LexemeToTagMapping> pStandardFuncMapping, 
            CharValidationRule charValidationRule,
            size_t maxIdentifierLength);

        virtual bool TryCreateToken(
            const string_type& lexeme, 
            int lineNum, 
            int charNum, 
            Token** token, 
            LexicalError** error);

    private:
        boost::shared_ptr<LexemeToTagMapping> pKeywordsMapping;
        boost::shared_ptr<LexemeToTagMapping> pStandardFuncMapping;
        CharValidationRule charValidationRule;
        size_t maxIdentifierLength;

        bool CheckCharset(const string_type& lexeme);
    };

}
}
}