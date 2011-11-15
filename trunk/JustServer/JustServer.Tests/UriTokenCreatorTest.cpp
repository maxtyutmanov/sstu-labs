#define BOOST_AUTO_TEST_MAIN
#include <boost/test/auto_unit_test.hpp>
#include <UriTokenCreator.h>
#include <UriToken.h>
#include <TokenTag.h>
#include <memory>
using std::auto_ptr;
using namespace JustServer::HttpGrammar;
using namespace JustServer::HttpGrammar::Tokens;

struct UriTokenCreatorFixture {
    UriTokenCreatorFixture() {
        tokenCreator.reset(new UriTokenCreator());
    }

    virtual ~UriTokenCreatorFixture() {}

    auto_ptr<UriTokenCreator> tokenCreator;
};

BOOST_FIXTURE_TEST_SUITE(UriTokenCreatorTestSuite, UriTokenCreatorFixture)

BOOST_AUTO_TEST_CASE( AbsoluteUri_OnlyHost ) {
    Token* pToken = NULL;
    LexicalError* pLexicalError = NULL;

    bool result = tokenCreator->TryCreateToken("http://www.google.com/", 0, 0, &pToken, &pLexicalError);

    BOOST_CHECK(result);
    BOOST_CHECK(pLexicalError == NULL);
    BOOST_ASSERT(pToken != NULL);
    BOOST_ASSERT(pToken->GetTag() == TokenTag::Uri);

    UriToken* pUriToken = (UriToken *)pToken;

    BOOST_CHECK(pUriToken->GetAbsolutePath() == "/");
    BOOST_CHECK(pUriToken->GetHost() == "www.google.com");
    BOOST_CHECK(pUriToken->GetPort() == UriToken::UnspecifiedPort);
    BOOST_CHECK(pUriToken->GetQuery().size() == 0);
    BOOST_CHECK(pUriToken->GetScheme() == "http");

    delete pToken;
    
    if (pLexicalError != NULL) {
        delete pLexicalError;
    }
}

BOOST_AUTO_TEST_CASE( AbsoluteUri_HostAndPort ) {
    Token* pToken = NULL;
    LexicalError* pLexicalError = NULL;

    bool result = tokenCreator->TryCreateToken("http://www.google.com:5555/", 0, 0, &pToken, &pLexicalError);

    BOOST_CHECK(result);
    BOOST_CHECK(pLexicalError == NULL);
    BOOST_ASSERT(pToken != NULL);
    BOOST_ASSERT(pToken->GetTag() == TokenTag::Uri);

    UriToken* pUriToken = (UriToken *)pToken;

    BOOST_CHECK(pUriToken->GetAbsolutePath() == "/");
    BOOST_CHECK(pUriToken->GetHost() == "www.google.com");
    BOOST_CHECK(pUriToken->GetPort() == 5555);
    BOOST_CHECK(pUriToken->GetQuery().size() == 0);
    BOOST_CHECK(pUriToken->GetScheme() == "http");

    delete pToken;
    
    if (pLexicalError != NULL) {
        delete pLexicalError;
    }
}

BOOST_AUTO_TEST_CASE( AbsoluteUri_HostPortAndPath ) {
    Token* pToken = NULL;
    LexicalError* pLexicalError = NULL;

    bool result = tokenCreator->TryCreateToken("http://www.google.com:5555/Documents/1", 0, 0, &pToken, &pLexicalError);

    BOOST_CHECK(result);
    BOOST_CHECK(pLexicalError == NULL);
    BOOST_ASSERT(pToken != NULL);
    BOOST_ASSERT(pToken->GetTag() == TokenTag::Uri);

    UriToken* pUriToken = (UriToken *)pToken;

    BOOST_CHECK(pUriToken->GetAbsolutePath() == "/Documents/1");
    BOOST_CHECK(pUriToken->GetHost() == "www.google.com");
    BOOST_CHECK(pUriToken->GetPort() == 5555);
    BOOST_CHECK(pUriToken->GetQuery().size() == 0);
    BOOST_CHECK(pUriToken->GetScheme() == "http");

    delete pToken;
    
    if (pLexicalError != NULL) {
        delete pLexicalError;
    }
}

BOOST_AUTO_TEST_CASE( AbsoluteUri_HostPortPathAndQuery ) {
    Token* pToken = NULL;
    LexicalError* pLexicalError = NULL;

    bool result = tokenCreator->TryCreateToken("http://www.google.com:5555/Documents/1?name1=value1&name2=", 0, 0, &pToken, &pLexicalError);

    BOOST_CHECK(result);
    BOOST_CHECK(pLexicalError == NULL);
    BOOST_ASSERT(pToken != NULL);
    BOOST_ASSERT(pToken->GetTag() == TokenTag::Uri);

    UriToken* pUriToken = (UriToken *)pToken;

    BOOST_CHECK(pUriToken->GetAbsolutePath() == "/Documents/1");
    BOOST_CHECK(pUriToken->GetHost() == "www.google.com");
    BOOST_CHECK(pUriToken->GetPort() == 5555);
    BOOST_CHECK(pUriToken->GetScheme() == "http");

    vector<NameValuePair> query = pUriToken->GetQuery();

    BOOST_ASSERT(query.size() == 2);
    BOOST_CHECK(query[0].name == "name1");
    BOOST_CHECK(query[0].value == "value1");
    BOOST_CHECK(query[1].name == "name2");
    BOOST_CHECK(query[1].value == "");

    delete pToken;
    
    if (pLexicalError != NULL) {
        delete pLexicalError;
    }
}

BOOST_AUTO_TEST_CASE( RelativeUri_Path ) {
    Token* pToken = NULL;
    LexicalError* pLexicalError = NULL;

    bool result = tokenCreator->TryCreateToken("/Documents/1", 0, 0, &pToken, &pLexicalError);

    BOOST_CHECK(result);
    BOOST_CHECK(pLexicalError == NULL);
    BOOST_ASSERT(pToken != NULL);
    BOOST_ASSERT(pToken->GetTag() == TokenTag::Uri);

    UriToken* pUriToken = (UriToken *)pToken;

    BOOST_CHECK(pUriToken->GetAbsolutePath() == "/Documents/1");
    BOOST_CHECK(pUriToken->GetHost() == "");
    BOOST_CHECK(pUriToken->GetPort() == UriToken::UnspecifiedPort);
    BOOST_CHECK(pUriToken->GetQuery().size() == 0);
    BOOST_CHECK(pUriToken->GetScheme() == "");

    delete pToken;
    
    if (pLexicalError != NULL) {
        delete pLexicalError;
    }
}

BOOST_AUTO_TEST_CASE( RelativeUri_PathAndQuery ) {
    Token* pToken = NULL;
    LexicalError* pLexicalError = NULL;

    bool result = tokenCreator->TryCreateToken("/Documents/1?name1=val1&name2=val2", 0, 0, &pToken, &pLexicalError);

    BOOST_CHECK(result);
    BOOST_CHECK(pLexicalError == NULL);
    BOOST_ASSERT(pToken != NULL);
    BOOST_ASSERT(pToken->GetTag() == TokenTag::Uri);

    UriToken* pUriToken = (UriToken *)pToken;

    BOOST_CHECK(pUriToken->GetAbsolutePath() == "/Documents/1");
    BOOST_CHECK(pUriToken->GetHost() == "");
    BOOST_CHECK(pUriToken->GetPort() == UriToken::UnspecifiedPort);
    BOOST_CHECK(pUriToken->GetScheme() == "");

    vector<NameValuePair> query = pUriToken->GetQuery();

    BOOST_ASSERT(query.size() == 2);
    BOOST_CHECK(query[0].name == "name1");
    BOOST_CHECK(query[0].value == "val1");
    BOOST_CHECK(query[1].name == "name2");
    BOOST_CHECK(query[1].value == "val2");

    delete pToken;
    
    if (pLexicalError != NULL) {
        delete pLexicalError;
    }
}

BOOST_AUTO_TEST_CASE( RelativeUri_EmptyPathAndQuery ) {
    Token* pToken = NULL;
    LexicalError* pLexicalError = NULL;

    bool result = tokenCreator->TryCreateToken("/?name1=val1&name2=val2", 0, 0, &pToken, &pLexicalError);

    BOOST_CHECK(result);
    BOOST_CHECK(pLexicalError == NULL);
    BOOST_ASSERT(pToken != NULL);
    BOOST_ASSERT(pToken->GetTag() == TokenTag::Uri);

    UriToken* pUriToken = (UriToken *)pToken;

    BOOST_CHECK(pUriToken->GetAbsolutePath() == "/");
    BOOST_CHECK(pUriToken->GetHost() == "");
    BOOST_CHECK(pUriToken->GetPort() == UriToken::UnspecifiedPort);
    BOOST_CHECK(pUriToken->GetScheme() == "");

    vector<NameValuePair> query = pUriToken->GetQuery();

    BOOST_ASSERT(query.size() == 2);
    BOOST_CHECK(query[0].name == "name1");
    BOOST_CHECK(query[0].value == "val1");
    BOOST_CHECK(query[1].name == "name2");
    BOOST_CHECK(query[1].value == "val2");

    delete pToken;
    
    if (pLexicalError != NULL) {
        delete pLexicalError;
    }
}

BOOST_AUTO_TEST_SUITE_END()