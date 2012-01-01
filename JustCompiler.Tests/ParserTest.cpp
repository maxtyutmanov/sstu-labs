#include <boost/test/auto_unit_test.hpp>
#include <FirstFunction.h>
#include <FollowFunction.h>
#include <Terminal.h>
#include <NonTerminal.h>
#include <FirstNFollowFactory.h>
#include <TokenTag.h>
#include <ParserTable.h>
#include <NonTerminalTag.h>
#include <SyntaxError.h>
#include <SyntaxDirectedParser.h>
#include <TokenStream.h>
#include <Tokens.h>
#include <ErrorClass.h>
#include "TestGrammarFactory.h"

using namespace JustCompiler::SyntacticAnalyzer::ContextFreeGrammar;
using namespace JustCompiler::SyntacticAnalyzer;
using namespace JustCompiler::ParserGrammar;
using namespace JustCompiler::LexicalAnalyzer;
using namespace JustCompiler::LexicalAnalyzer::Tokens;
using namespace JustCompiler::Tests;
using namespace std;

struct ArithmeticExprParserFixture {
    virtual ~ArithmeticExprParserFixture() {}

    static Grammar exprGrammar;
};

Grammar ArithmeticExprParserFixture::exprGrammar(TestGrammarFactory::CreateExpressionsGrammar());

BOOST_FIXTURE_TEST_SUITE( ArithmeticExprParserSuite, ArithmeticExprParserFixture )

BOOST_AUTO_TEST_CASE( ParseArithmeticExpression_Valid ) {
    PFirstFunction pFirst = FirstNFollowFactory::GetFirst(exprGrammar);
    PFollowFunction pFollow = FirstNFollowFactory::GetFollow(exprGrammar, pFirst);
    ParserTable parserTable(exprGrammar, *pFirst, *pFollow);

    vector<PToken> tokens;
    tokens.push_back(PToken(new Identifier(L"a", 1, 1)));
    tokens.push_back(PToken(new Token(TokenTag::Plus)));
    tokens.push_back(PToken(new Identifier(L"b", 1, 1)));
    tokens.push_back(PToken(new Token(SpecialTokenTag::Eof, 2, 1)));

    boost::shared_ptr<ITokenStream> tokenStream(new TokenStream(tokens));

    SyntaxDirectedParser parser(exprGrammar, parserTable);

    auto_ptr<ParserOutput> output = parser.Parse(tokenStream);

    BOOST_CHECK(output->errors.size() == 0);
}

BOOST_AUTO_TEST_CASE( ParseArithmeticExpression_Valid2 ) {
    PFirstFunction pFirst = FirstNFollowFactory::GetFirst(exprGrammar);
    PFollowFunction pFollow = FirstNFollowFactory::GetFollow(exprGrammar, pFirst);
    ParserTable parserTable(exprGrammar, *pFirst, *pFollow);

    vector<PToken> tokens;
    tokens.push_back(PToken(new Identifier(L"id", 1, 2)));
    tokens.push_back(PToken(new Token(TokenTag::Plus)));
    tokens.push_back(PToken(new Identifier(L"id", 1, 4)));
    tokens.push_back(PToken(new Token(TokenTag::Asterisk)));
    tokens.push_back(PToken(new Identifier(L"id", 1, 6)));
    tokens.push_back(PToken(new Token(SpecialTokenTag::Eof, 2, 1)));

    boost::shared_ptr<ITokenStream> tokenStream(new TokenStream(tokens));

    SyntaxDirectedParser parser(exprGrammar, parserTable);

    auto_ptr<ParserOutput> output = parser.Parse(tokenStream);

    BOOST_CHECK(output->errors.size() == 0);
}

BOOST_AUTO_TEST_CASE( ParseArithmeticExpression_Invalid ) {
    PFirstFunction pFirst = FirstNFollowFactory::GetFirst(exprGrammar);
    PFollowFunction pFollow = FirstNFollowFactory::GetFollow(exprGrammar, pFirst);
    ParserTable parserTable(exprGrammar, *pFirst, *pFollow);

    vector<PToken> tokens;
    tokens.push_back(PToken(new Identifier(L"id", 1, 2)));
    tokens.push_back(PToken(new Token(TokenTag::Plus)));
    tokens.push_back(PToken(new Identifier(L"id", 1, 4)));
    tokens.push_back(PToken(new Token(TokenTag::Asterisk)));
    tokens.push_back(PToken(new Token(SpecialTokenTag::Eof, 2, 1)));

    boost::shared_ptr<ITokenStream> tokenStream(new TokenStream(tokens));

    SyntaxDirectedParser parser(exprGrammar, parserTable);

    auto_ptr<ParserOutput> output = parser.Parse(tokenStream);

    BOOST_ASSERT(output->errors.size() == 1);

    BOOST_CHECK(output->errors[0]->GetErrorClass() == ErrorClass::UnexpectedEndOfFile);
}

BOOST_AUTO_TEST_CASE( ParseArithmeticExpression_Invalid2 ) {
    PFirstFunction pFirst = FirstNFollowFactory::GetFirst(exprGrammar);
    PFollowFunction pFollow = FirstNFollowFactory::GetFollow(exprGrammar, pFirst);
    ParserTable parserTable(exprGrammar, *pFirst, *pFollow);

    vector<PToken> tokens;
    tokens.push_back(PToken(new Identifier(L"id", 1, 2)));
    tokens.push_back(PToken(new Token(TokenTag::Plus)));
    tokens.push_back(PToken(new Token(TokenTag::Asterisk)));
    tokens.push_back(PToken(new Token(SpecialTokenTag::Eof, 2, 1)));

    boost::shared_ptr<ITokenStream> tokenStream(new TokenStream(tokens));

    SyntaxDirectedParser parser(exprGrammar, parserTable);

    auto_ptr<ParserOutput> output = parser.Parse(tokenStream);

    BOOST_ASSERT(output->errors.size() == 1);

    BOOST_CHECK(output->errors[0]->GetErrorClass() == ErrorClass::UnexpectedToken);
}

BOOST_AUTO_TEST_CASE( ParseArithmeticExpression_Invalid3 ) {
    PFirstFunction pFirst = FirstNFollowFactory::GetFirst(exprGrammar);
    PFollowFunction pFollow = FirstNFollowFactory::GetFollow(exprGrammar, pFirst);
    ParserTable parserTable(exprGrammar, *pFirst, *pFollow);

    vector<PToken> tokens;
    tokens.push_back(PToken(new Identifier(L"id", 1, 2)));
    tokens.push_back(PToken(new Token(TokenTag::Asterisk)));
    tokens.push_back(PToken(new Token(TokenTag::OpeningRoundBracket)));
    tokens.push_back(PToken(new Identifier(L"id", 1, 4)));
    tokens.push_back(PToken(new Token(TokenTag::Plus)));
    tokens.push_back(PToken(new Identifier(L"id", 1, 6)));
    tokens.push_back(PToken(new Token(SpecialTokenTag::Eof, 2, 1)));

    boost::shared_ptr<ITokenStream> tokenStream(new TokenStream(tokens));

    SyntaxDirectedParser parser(exprGrammar, parserTable);

    auto_ptr<ParserOutput> output = parser.Parse(tokenStream);

    BOOST_ASSERT(output->errors.size() == 1);
    BOOST_CHECK(output->errors[0]->GetErrorClass() == ErrorClass::UnexpectedEndOfFile);
}

BOOST_AUTO_TEST_SUITE_END()