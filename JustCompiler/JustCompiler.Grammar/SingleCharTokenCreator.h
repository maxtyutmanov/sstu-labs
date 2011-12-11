#pragma once

#include "Global.h"
#include "TokenCreator.h"
#include "LexemeToTagMapping.h"
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace LexicalAnalyzer {
namespace TokenCreators {

    class SingleCharTokenCreator : public TokenCreator {
    public:
        SingleCharTokenCreator(boost::shared_ptr<LexemeToTagMapping> pSingleCharLexemesMapping);

        virtual bool TryCreateToken(
            const string_type& lexeme, 
            int lineNum, 
            int charNum, 
            Token** token, 
            LexicalError** error);

    private:
        boost::shared_ptr<LexemeToTagMapping> pSingleCharLexemesMapping;
    };

}
}
}