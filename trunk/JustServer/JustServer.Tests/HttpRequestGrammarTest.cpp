#include <boost/test/auto_unit_test.hpp>
#include <HttpRequestGrammar.h>
#include "LexerInputBuffer.h"
#include <HttpVerb.h>
#include <UriToken.h>
#include <TokenTag.h>
#include <HttpTextToken.h>
#include <HeaderToken.h>
#include <HttpVersionToken.h>
#include <memory>
#include <string>
#include <sstream>
using std::auto_ptr;
using std::string;
using std::istringstream;
using namespace JustServer::HttpGrammar;
//using namespace JustServer::HttpGrammar::Tokens;

struct HttpRequestGrammarFixture {
    HttpRequestGrammarFixture() {
        pLexer = HttpRequestGrammar::CreateLexer();
    }

    virtual ~HttpRequestGrammarFixture() {}

    void Tokenize(const string& input) {
        istringstream inputStream(input);
        
        auto_ptr<IInputBuffer> pInputBuffer(new LexerInputBuffer(inputStream));
        
        pLexer->SetInput(pInputBuffer);

        LexerOutput output = pLexer->Tokenize();

        tokens = output.get<0>();
        errors = output.get<1>();
    }

    auto_ptr<Lexer> pLexer;
    vector<shared_ptr<Token>> tokens;
    vector<shared_ptr<LexicalError>> errors;
};

BOOST_FIXTURE_TEST_SUITE( HttpRequestGrammarTestSuite, HttpRequestGrammarFixture )

BOOST_AUTO_TEST_CASE( SmokeTest ) {
    string requestText;

    requestText.append(
        "GET /?q=helloworld&type=test HTTP/1.1\r\n");
    requestText.append(
        "Host : www.google.com\r\n\r\n");

    Tokenize(requestText);

    BOOST_CHECK(errors.size() == 0);
    BOOST_ASSERT(tokens.size() == 4);

    BOOST_ASSERT(tokens[0]->GetTag() == TokenTag::HttpVerb);
    BOOST_ASSERT(tokens[1]->GetTag() == TokenTag::Uri);
    BOOST_ASSERT(tokens[2]->GetTag() == TokenTag::HttpVersion);
    BOOST_ASSERT(tokens[3]->GetTag() == TokenTag::Header);

    Tokens::HttpVerb* pVerb = (Tokens::HttpVerb*)tokens[0].get();

    BOOST_CHECK(pVerb->VerbName() == "GET");

    Tokens::UriToken* pUri = (Tokens::UriToken*)tokens[1].get();

    BOOST_CHECK(pUri->GetAbsolutePath() == "/");
    BOOST_CHECK(pUri->GetHost() == "");
    BOOST_CHECK(pUri->GetPort() == Tokens::UriToken::UnspecifiedPort);
    BOOST_CHECK(pUri->GetScheme() == "");

    vector<NameValuePair> query = pUri->GetQuery();

    BOOST_ASSERT(query.size() == 2);
    BOOST_CHECK(query[0].name == "q");
    BOOST_CHECK(query[0].value == "helloworld");
    BOOST_CHECK(query[1].name == "type");
    BOOST_CHECK(query[1].value == "test");

    Tokens::HttpVersionToken* pVersion = (Tokens::HttpVersionToken*)tokens[2].get();
    BOOST_CHECK(pVersion->GetMajor() == 1);
    BOOST_CHECK(pVersion->GetMinor() == 1);

    Tokens::HeaderToken* pHeader = (Tokens::HeaderToken*)tokens[3].get();
    BOOST_CHECK(pHeader->GetName() == "Host");
    BOOST_CHECK(pHeader->GetValue() == "www.google.com");
}

BOOST_AUTO_TEST_CASE( WithBody ) {
    string requestText;

    requestText.append(
        "POST /?q=helloworld&type=test HTTP/1.1\r\n");
    requestText.append(
        "Host : www.google.com\r\n\r\n");
    requestText.append(
        "param1=value1&param2=value2&param3=value3");

    Tokenize(requestText);

    BOOST_CHECK(errors.size() == 0);
    BOOST_ASSERT(tokens.size() == 5);

    BOOST_ASSERT(tokens[0]->GetTag() == TokenTag::HttpVerb);
    BOOST_ASSERT(tokens[1]->GetTag() == TokenTag::Uri);
    BOOST_ASSERT(tokens[2]->GetTag() == TokenTag::HttpVersion);
    BOOST_ASSERT(tokens[3]->GetTag() == TokenTag::Header);
    BOOST_ASSERT(tokens[4]->GetTag() == TokenTag::Body);

    Tokens::HttpVerb* pVerb = (Tokens::HttpVerb*)tokens[0].get();
    BOOST_CHECK(pVerb->VerbName() == "POST");

    Tokens::UriToken* pUri = (Tokens::UriToken*)tokens[1].get();

    BOOST_CHECK(pUri->GetAbsolutePath() == "/");
    BOOST_CHECK(pUri->GetHost() == "");
    BOOST_CHECK(pUri->GetPort() == Tokens::UriToken::UnspecifiedPort);
    BOOST_CHECK(pUri->GetScheme() == "");

    vector<NameValuePair> query = pUri->GetQuery();

    BOOST_ASSERT(query.size() == 2);
    BOOST_CHECK(query[0].name == "q");
    BOOST_CHECK(query[0].value == "helloworld");
    BOOST_CHECK(query[1].name == "type");
    BOOST_CHECK(query[1].value == "test");

    Tokens::HttpVersionToken* pVersion = (Tokens::HttpVersionToken*)tokens[2].get();
    BOOST_CHECK(pVersion->GetMajor() == 1);
    BOOST_CHECK(pVersion->GetMinor() == 1);

    Tokens::HeaderToken* pHeader = (Tokens::HeaderToken*)tokens[3].get();
    BOOST_CHECK(pHeader->GetName() == "Host");
    BOOST_CHECK(pHeader->GetValue() == "www.google.com");

    Tokens::HttpTextToken* pBody = (Tokens::HttpTextToken*)tokens[4].get();
    BOOST_CHECK(pBody->GetText() == "param1=value1&param2=value2&param3=value3");
}

BOOST_AUTO_TEST_SUITE_END()