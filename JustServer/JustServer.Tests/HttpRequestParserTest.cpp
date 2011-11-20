#include <boost/test/auto_unit_test.hpp>
#include <HttpRequestParser.h>
#include <vector>
#include <Token.h>
#include <HttpTextToken.h>
#include <UriToken.h>
#include <HttpVersionToken.h>
#include <HeaderToken.h>
#include <boost/shared_ptr.hpp>
using std::vector;
using namespace JustServer::Http;
using boost::shared_ptr;

using namespace JustServer::Utility;
using namespace JustServer::HttpGrammar::Tokens;
using JustServer::HttpGrammar::TokenTag;

struct HttpRequestParserFixture {
    virtual ~HttpRequestParserFixture() {}

    HttpRequestParser parser;
};

BOOST_FIXTURE_TEST_SUITE( HttpRequestParserTestSuite, HttpRequestParserFixture )

BOOST_AUTO_TEST_CASE( SmokeTest ) {
    vector<shared_ptr<Token>> tokens;

    vector<NameValuePair> query;
    query.push_back(NameValuePair("param", "val"));

    tokens.push_back(shared_ptr<HttpTextToken>(new HttpTextToken(TokenTag::HttpVerb, "GET")));
    tokens.push_back(shared_ptr<UriToken>(new UriToken("http", "localhost", "/helloworld", query)));
    tokens.push_back(shared_ptr<HttpVersionToken>(new HttpVersionToken(1, 1)));
    tokens.push_back(shared_ptr<HeaderToken>(new HeaderToken("host", "www.google.com")));

    HttpRequest requestObj = parser.ParseRequest(tokens);

    BOOST_CHECK(requestObj.GetVerb() == "GET");

    Uri requestUri = requestObj.GetRequestUri();

    BOOST_CHECK(requestUri.GetHost() == "localhost");
    BOOST_CHECK(requestUri.GetPort() == 80);
    BOOST_CHECK(requestUri.GetScheme() == "http");

    vector<NameValuePair> queryObj = requestUri.Query();

    BOOST_ASSERT(queryObj.size() == 1);
    BOOST_CHECK(queryObj[0].name == "param");
    BOOST_CHECK(queryObj[0].value == "val");
}

BOOST_AUTO_TEST_SUITE_END()