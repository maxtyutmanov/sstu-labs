#include <boost/test/auto_unit_test.hpp>
#include <HttpVersionToken.h>
#include <HttpVersionTokenCreator.h>
#include <TokenTag.h>
#include <memory>
using std::auto_ptr;
using namespace JustServer::HttpGrammar;
using namespace JustServer::HttpGrammar::Tokens;

struct HttpVersionTokenCreatorFixture {
    HttpVersionTokenCreatorFixture() {
        tokenCreator.reset(new HttpVersionTokenCreator());
        pToken = NULL;
        pError = NULL;
    }

    virtual ~HttpVersionTokenCreatorFixture() {
        if (pToken != NULL) {
            delete pToken;
        }

        if (pError != NULL) {
            delete pError;
        }
    }

    auto_ptr<HttpVersionTokenCreator> tokenCreator;
    Token* pToken;
    LexicalError* pError;
};

BOOST_FIXTURE_TEST_SUITE(HttpVersionTokenCreatorTestSuite, HttpVersionTokenCreatorFixture)

BOOST_AUTO_TEST_CASE( CorrectHttpVersion ) {
    bool success = tokenCreator->TryCreateToken("HTTP/1.0", 0, 0, &pToken, &pError);

    BOOST_ASSERT(success);
    BOOST_ASSERT(pToken != NULL);
    BOOST_CHECK(pError == NULL);
    BOOST_ASSERT(pToken->GetTag() == TokenTag::HttpVersion);

    HttpVersionToken* pHttpVersionToken = (HttpVersionToken*)pToken;

    BOOST_CHECK(pHttpVersionToken->GetMajor() == 1);
    BOOST_CHECK(pHttpVersionToken->GetMinor() == 0);
}

BOOST_AUTO_TEST_CASE( InvalidHttpVersion ) {
    bool success = tokenCreator->TryCreateToken("HTTP/1s.0", 0, 0, &pToken, &pError);

    BOOST_ASSERT(!success);
    BOOST_ASSERT(pToken == NULL);
    BOOST_CHECK(pError != NULL);
}

BOOST_AUTO_TEST_SUITE_END()