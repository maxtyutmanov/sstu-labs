#pragma once

#include "Global.h"
#include "TokenCreator.h"

//TODO: consider deleting of this class

namespace JustCompiler {
namespace LexicalAnalyzer {
namespace TokenCreators {

    class UnrecognizedTokenCreator : public TokenCreator {
    public:
        virtual bool TryCreateToken(
            const string_type& lexeme, 
            int lineNum, 
            int charNum, 
            Token** token, 
            LexicalError** error);
    };

}
}
}