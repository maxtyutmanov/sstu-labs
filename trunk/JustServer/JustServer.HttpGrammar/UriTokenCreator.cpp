#include "UriTokenCreator.h"
#include "UriToken.h"
#include <assert.h>
#include <algorithm>
#include <functional>
#include <iterator>
#include <boost/lexical_cast.hpp>

using namespace JustServer::HttpGrammar::Tokens;

namespace JustServer {
namespace HttpGrammar {

    bool UriTokenCreator::TryCreateToken(
        const string& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error) {

        string schemeStr;
        string host;
        unsigned short port;
        string absolutePath;
        string query;
        bool portIsSpecified = false;

        string::const_iterator pathIt;

        //parse uri scheme (e.g. http or https)

        const string scheme_end = "://";

        string::const_iterator schemeEndIt = std::search(lexeme.begin(), lexeme.end(), scheme_end.begin(), scheme_end.end());

        if (schemeEndIt != lexeme.end()) {
            //end of scheme was found => scheme is present in uri => uri is absolute

            std::transform(lexeme.begin(), schemeEndIt, std::back_inserter(schemeStr), std::ptr_fun<int, int>(tolower));

            //host and port parsing

            //...moving to the start of host
            std::advance(schemeEndIt, scheme_end.size());

            //...searching for the end of host and (not necessarily) port
            string::const_iterator hostAndPortEndIt = std::find(schemeEndIt, lexeme.end(), '/');

            if (hostAndPortEndIt != lexeme.end() && hostAndPortEndIt != schemeEndIt) {
                string hostAndPortStr;
                std::transform(schemeEndIt, hostAndPortEndIt, std::back_inserter(hostAndPortStr), std::ptr_fun<int, int>(tolower));

                if (TryParseHostAndPort(hostAndPortStr, host, portIsSpecified, port)) {
                    pathIt = hostAndPortEndIt;
                }
                else {
                    //failed to parse host and port
                    *error = new LexicalError(lineNum, charNum, -1);
                    return false;
                }
            }
            else {
                //host is required when URI is absolute

                *error = new LexicalError(lineNum, charNum, -1);
                return false;
            }
        }
        else {
            //URI is relative => it starts with a path

            pathIt = lexeme.begin();
        }
        
        //searching for the end of absolute path
        string::const_iterator queryIt = std::find(pathIt, lexeme.end(), '?');
        absolutePath.assign(pathIt, queryIt);

        if (queryIt != lexeme.end()) {
            //moving to the start of query
            ++queryIt;
        }

        query.assign(queryIt, lexeme.end());

        vector<NameValuePair> parsedQuery;

        if (!TryParseQueryString(query, parsedQuery)) {
            *error = new LexicalError(lineNum, charNum, -1);
            return false;
        }

        if (portIsSpecified) {
            *token = new UriToken(schemeStr, host, port, absolutePath, parsedQuery);
        }
        else {
            *token = new UriToken(schemeStr, host, absolutePath, parsedQuery);
        }

        return true;
    }

    bool UriTokenCreator::TryParseHostAndPort(
        const string& hostAndPort,
        string& host,
        bool& portIsSpecified,
        unsigned short& port) {

        string::const_iterator portIt = std::find(hostAndPort.begin(), hostAndPort.end(), ':');

        //parsing a host
        
        string tmpHost(hostAndPort.begin(), portIt);

        if (tmpHost.length() == 0) {
            return false;
        }

        if (portIt != hostAndPort.end()) {
            //there is a colon in uri => there must be a port number
            
            ++portIt;

            //parsing a port

            string tmpPortStr(portIt, hostAndPort.end());

            if (tmpPortStr.length() == 0) {
                return false;
            }
            else {
                try {
                    port = boost::lexical_cast<unsigned short, string>(tmpPortStr);
                    host = tmpHost;
                    portIsSpecified = true;
                    return true;
                }
                catch (const boost::bad_lexical_cast) {
                    return false;
                }
            }
        }
        else {
            //port number isn't specified, but host is OK
            portIsSpecified = false;
            host = tmpHost;
            return true;
        }
    }

    bool UriTokenCreator::TryParseQueryString(
        const string& query,
        vector<NameValuePair>& params) {

        vector<NameValuePair> parsedQuery;

        string::const_iterator nameBeginIt = query.begin();
        string::const_iterator nameEndIt;
        string::const_iterator valueBeginIt;
        string::const_iterator valueEndIt;

        while (nameBeginIt != query.end()) {
            nameEndIt = std::find(nameBeginIt, query.end(), '=');

            if (nameEndIt == query.end()) {
                //error: if there is a name of parameter there must be at least equals sign
                return false;
            }

            string name(nameBeginIt, nameEndIt);

            //skipping the equals sign
            string::const_iterator valueBeginIt = nameEndIt + 1;

            string::const_iterator valueEndIt = std::find(valueBeginIt, query.end(), '&');

            string value(valueBeginIt, valueEndIt);

            parsedQuery.push_back(NameValuePair(name, value));

            if (valueEndIt != query.end()) {
                //skipping the ampersand sign
                nameBeginIt = valueEndIt + 1;
            }
            else {
                nameBeginIt = query.end();
            }
        }

        //TODO: very interesting, what is really happening here. Wikipedia says that it's OK
        params = parsedQuery;
        return true;
    }
}
}