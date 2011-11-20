#include <boost/test/auto_unit_test.hpp>
#include <HeaderTokenCreator.h>
#include <HeaderToken.h>
#include <TokenTag.h>
#include <memory>
using std::auto_ptr;
using namespace JustServer::HttpGrammar;
using namespace JustServer::HttpGrammar::Tokens;


struct HeaderTokenCreatorFixture {
    HeaderTokenCreatorFixture() {
        tokenCreator.reset(new HeaderTokenCreator());
        pToken = NULL;
        pLexicalError = NULL;
    }

    virtual ~HeaderTokenCreatorFixture() {
        if (pToken != NULL) {
            delete pToken;
        }

        if (pLexicalError != NULL) {
            delete pLexicalError;
        }
    }

    auto_ptr<HeaderTokenCreator> tokenCreator;
    Token* pToken;
    LexicalError* pLexicalError;
};

BOOST_FIXTURE_TEST_SUITE( HeaderTokenCreatorTestSuite, HeaderTokenCreatorFixture )

BOOST_AUTO_TEST_CASE( SmokeTest ) {
    bool result = tokenCreator->TryCreateToken("Content-Length : 203", 0, 0, &pToken, &pLexicalError);

    BOOST_CHECK(result);
    BOOST_CHECK(pLexicalError == NULL);
    BOOST_ASSERT(pToken != NULL);
    BOOST_ASSERT(pToken->GetTag() == TokenTag::Header);

    HeaderToken* pHeaderToken = (HeaderToken *)pToken;

    BOOST_CHECK(pHeaderToken->GetName() == "Content-Length");
    BOOST_CHECK(pHeaderToken->GetValue() == "203");
}

BOOST_AUTO_TEST_SUITE_END()