#include "HeaderTokenCreator.h"
#include "HeaderToken.h"
#include <algorithm>
#include <iterator>
#include <boost/algorithm/string.hpp>

using namespace JustServer::HttpGrammar::Tokens;

namespace JustServer {
namespace HttpGrammar {

    bool HeaderTokenCreator::TryCreateToken(
        const string& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error) {

        //TODO: finish the implementation

        string name;
        string value;

        string::const_iterator headerNameEndIt = std::find(lexeme.begin(), lexeme.end(), ':');

        if (headerNameEndIt != lexeme.end()) {
            name.assign(lexeme.begin(), headerNameEndIt);

            //skipping the colon and moving to the start of header value
            string::const_iterator headerValueStartIt = headerNameEndIt + 1;

            value.assign(headerValueStartIt, lexeme.end());

            boost::trim(name);
            boost::trim(value);

            if (name.length() != 0 && value.length() != 0) {
                *token = new HeaderToken(name, value);
                return true;
            }
        }

        *error = new LexicalError(lineNum, charNum, -1);
        return false;
    }

}
}