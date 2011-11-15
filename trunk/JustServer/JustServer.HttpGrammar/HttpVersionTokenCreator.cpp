#include "HttpVersionTokenCreator.h"
#include "HttpVersionToken.h"
#include <algorithm>
#include <iterator>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

using JustServer::HttpGrammar::Tokens::HttpVersionToken;

namespace JustServer {
namespace HttpGrammar {

    bool HttpVersionTokenCreator::TryCreateToken(
        const string_type& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error) {

        //TODO: move to class' fields
        boost::regex versionRegex("HTTP/(\\d+)\\.(\\d+)");

        boost::match_results<string::const_iterator> matchResults;

        if (boost::regex_match(lexeme, matchResults, versionRegex)) {
            string majorStr = matchResults[1].str();
            string minorStr = matchResults[2].str();
            
            try {
                unsigned int major = boost::lexical_cast<unsigned int, string>(majorStr);
                unsigned int minor = boost::lexical_cast<unsigned int, string>(minorStr);

                *token = new HttpVersionToken(major, minor);
                return true;
            }
            catch (const boost::bad_lexical_cast& ex) {
                *error = new LexicalError(lineNum, charNum, -1);
                return false;
            }
        }
        else {
            *error = new LexicalError(lineNum, charNum, -1);
            return false;
        }
    }

}
}