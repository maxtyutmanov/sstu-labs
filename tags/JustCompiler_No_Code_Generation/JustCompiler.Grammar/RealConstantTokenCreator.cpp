#include "RealConstantTokenCreator.h"
#include "RealConstant.h"
#include "ErrorCode.h"
#include <boost/lexical_cast.hpp>

using JustCompiler::LexicalAnalyzer::Tokens::RealConstant;

namespace JustCompiler {
namespace LexicalAnalyzer {
namespace TokenCreators {

    bool RealConstantTokenCreator::TryCreateToken(
        const string_type& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error) {

        try {
            double value = boost::lexical_cast<double, string_type>(lexeme);
            *token = new RealConstant(value, lineNum, charNum - lexeme.length());
            return true;
        }
        catch (boost::bad_lexical_cast ex) {
            *error = new LexicalError(lineNum, charNum, ErrorCode::TooLargeRealConstant);
            return false;
        }
    }

}
}
}