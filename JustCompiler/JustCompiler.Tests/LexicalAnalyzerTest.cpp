#define BOOST_AUTO_TEST_MAIN
#include <boost/test/auto_unit_test.hpp>

#include "IntConstant.h"
#include "StringLiteral.h"
#include "Identifier.h"
#include <Lexer.h>
#include <sstream>
#include <string>
#include <MyGrammar.h>
#include <LexerInputBuffer.h>
using std::wistringstream;
using std::wstring;

using namespace JustCompiler::LexicalAnalyzer;
using namespace JustCompiler::LexicalAnalyzer::Tokens;

struct LexerFixture {
    virtual ~LexerFixture() {}

    void Tokenize(const wstring& source) {
        wistringstream sourceStream(source);
        auto_ptr<Lexer> pLexer = MyGrammar::CreateLexer();

        pLexer->SetInput(auto_ptr<IInputBuffer>(new LexerInputBuffer(sourceStream)));

        lexerOutput = pLexer->Tokenize();
    }

    LexerOutput lexerOutput;
};

BOOST_FIXTURE_TEST_SUITE( LexicalAnalysisTestSuite, LexerFixture )

BOOST_AUTO_TEST_CASE( Lexer_TokenizeWhiteSpaces ) {
    wstring source = L"    \t     \t\t       ";
    Tokenize(source);

    vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
    vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

    BOOST_CHECK(errors.size() == 0);
    BOOST_CHECK(tokens.size() == 0);
}

BOOST_AUTO_TEST_CASE( Lexer_TokenizeIntConstants ) {
    wstring source = L"    \t   99  \t\t     33";
    Tokenize(source);

    vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
    vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

    BOOST_CHECK(errors.size() == 0);
    BOOST_ASSERT(tokens.size() == 2);
    BOOST_ASSERT(tokens[0]->GetTag() == TokenTag::IntConstant);
    BOOST_ASSERT(tokens[1]->GetTag() == TokenTag::IntConstant);

    IntConstant* intConstant = (IntConstant*)tokens[0].get();
    BOOST_CHECK(intConstant->GetValue() == 99);
    intConstant = (IntConstant*)tokens[1].get();
    BOOST_CHECK(intConstant->GetValue() == 33);
}

BOOST_AUTO_TEST_CASE( Lexer_TokenizeIntConstants_Overflow_LastInvalid ) {
    wstring source = L"    \t   99  \t\t     999999999999999";
    Tokenize(source);

    vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
    vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

    BOOST_ASSERT(errors.size() == 1);
    BOOST_CHECK(errors[0]->GetLineNumber() == 1);

    BOOST_ASSERT(tokens.size() == 2);
    BOOST_CHECK(tokens[0]->GetTag() == TokenTag::IntConstant);
    BOOST_CHECK(tokens[1]->GetTag() == TokenTag::Unrecognized);
}

BOOST_AUTO_TEST_CASE( Lexer_TokenizeIntConstants_Overflow_NotLastInvalid ) {
    wstring source = L"    \t   99  \t\t \n    999999999999999    ";
    Tokenize(source);

    vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
    vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

    BOOST_ASSERT(errors.size() == 1);
    BOOST_CHECK(errors[0]->GetLineNumber() == 2);

    BOOST_ASSERT(tokens.size() == 2);
    BOOST_CHECK(tokens[0]->GetTag() == TokenTag::IntConstant);
    BOOST_CHECK(tokens[1]->GetTag() == TokenTag::Unrecognized);
}

BOOST_AUTO_TEST_CASE( Lexer_TokenizeIntConstants_InvalidIdentifier ) {
    wstring source = L"    \t   99  \t\t     99999999a999999    ";
    Tokenize(source);

    vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
    vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

    BOOST_ASSERT(errors.size() == 1);
    BOOST_CHECK(errors[0]->GetLineNumber() == 1);

    BOOST_ASSERT(tokens.size() == 2);
    BOOST_CHECK(tokens[0]->GetTag() == TokenTag::IntConstant);
    BOOST_CHECK(tokens[1]->GetTag() == TokenTag::Unrecognized);
}

BOOST_AUTO_TEST_CASE( Lexer_TokenizeStringLiterals ) {
    wstring source = L"    \"hello world\"    ";
    Tokenize(source);

    vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
    vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

    BOOST_CHECK(errors.size() == 0);
    BOOST_ASSERT(tokens.size() == 1);
    BOOST_ASSERT(tokens[0]->GetTag() == TokenTag::StringLiteral);

    StringLiteral* stringLiteral = (StringLiteral*)tokens[0].get();

    BOOST_CHECK(stringLiteral->GetText() == L"hello world");
}

BOOST_AUTO_TEST_CASE( Lexer_TokenizeStringLiterals_Unterminated_Eof ) {
    wstring source = L"    \"hello world    ";
    Tokenize(source);

    vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
    vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

    BOOST_CHECK(errors.size() == 1);
    BOOST_ASSERT(tokens.size() == 1);
    BOOST_CHECK(tokens[0]->GetTag() == TokenTag::Unrecognized);
}

BOOST_AUTO_TEST_CASE( Lexer_TokenizeStringLiterals_Unterminated_Eoln ) {
    wstring source = L"    \"hello world  \n  \t";
    Tokenize(source);

    vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
    vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

    BOOST_CHECK(errors.size() == 1);
    BOOST_ASSERT(tokens.size() == 1);
    BOOST_CHECK(tokens[0]->GetTag() == TokenTag::Unrecognized);
}

BOOST_AUTO_TEST_CASE( Lexer_TokenizeKeyword ) {
    wstring source = L"  for  \n  ";
    Tokenize(source);

    vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
    vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

    BOOST_CHECK(errors.size() == 0);
    BOOST_ASSERT(tokens.size() == 1);
    BOOST_CHECK(tokens[0]->GetTag() == TokenTag::For);
}

BOOST_AUTO_TEST_CASE( Lexer_TokenizeKeyword_Eoln ) {
    wstring source = L"  for\n  ";
    Tokenize(source);

    vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
    vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

    BOOST_CHECK(errors.size() == 0);
    BOOST_ASSERT(tokens.size() == 1);
    BOOST_CHECK(tokens[0]->GetTag() == TokenTag::For);
}

BOOST_AUTO_TEST_CASE( Lexer_TokenizeKeyword_Eof ) {
    wstring source = L"  for";
    Tokenize(source);

    vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
    vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

    BOOST_CHECK(errors.size() == 0);
    BOOST_ASSERT(tokens.size() == 1);
    BOOST_CHECK(tokens[0]->GetTag() == TokenTag::For);
}

BOOST_AUTO_TEST_CASE( Lexer_TokenizeIdentifier ) {
    wstring source = L"  i  \n  \t";
    Tokenize(source);

    vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
    vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

    BOOST_CHECK(errors.size() == 0);
    BOOST_ASSERT(tokens.size() == 1);
    BOOST_CHECK(tokens[0]->GetTag() == TokenTag::Identifier);

    Identifier* identifier = (Identifier*)tokens[0].get();

    BOOST_CHECK(identifier->GetName() == L"i");
}

BOOST_AUTO_TEST_CASE( Lexer_TokenizeIdentifier_TooLong ) {
    wstring source = L" \n  \n\n iasdasdasdasdasd  \n  \t";
    Tokenize(source);

    vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
    vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

    BOOST_ASSERT(errors.size() == 1);
    BOOST_CHECK(errors[0]->GetLineNumber() == 4);
    
    BOOST_ASSERT(tokens.size() == 1);
    BOOST_CHECK(tokens[0]->GetTag() == TokenTag::Unrecognized);
}

BOOST_AUTO_TEST_CASE( Lexer_TokenizeComment_OneLine ) {
    wstring source = L"/*this is comment!!!*/";
    Tokenize(source);

    vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
    vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

    BOOST_CHECK(errors.size() == 0);
    BOOST_CHECK(tokens.size() == 0);
}

BOOST_AUTO_TEST_CASE( Lexer_TokenizeComment_OneLine_SeparateAsteriskAndSlash ) {
    wstring source = L"/*this is comment!!!*   /";
    Tokenize(source);

    vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
    vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

    BOOST_CHECK(errors.size() == 1);
    BOOST_ASSERT(tokens.size() == 1);

    BOOST_CHECK(tokens[0]->GetTag() == TokenTag::Unrecognized);
}

BOOST_AUTO_TEST_CASE( Lexer_TokenizeComment_TwoLines ) {
    wstring source = L"a/*this is \ncomment!!!*/bc";
    Tokenize(source);

    vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
    vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

    BOOST_CHECK(errors.size() == 0);
    BOOST_ASSERT(tokens.size() == 2);

    BOOST_ASSERT(tokens[0]->GetTag() == TokenTag::Identifier);
    BOOST_ASSERT(tokens[1]->GetTag() == TokenTag::Identifier);

    Identifier* id = (Identifier*)tokens[0].get();

    BOOST_CHECK(id->GetName() == L"a");

    id = (Identifier*)tokens[1].get();

    BOOST_CHECK(id->GetName() == L"bc");
}

BOOST_AUTO_TEST_SUITE_END()