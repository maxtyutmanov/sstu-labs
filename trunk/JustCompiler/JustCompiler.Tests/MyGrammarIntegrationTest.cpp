#include <boost/test/auto_unit_test.hpp>

#include <MyGrammar.h>
#include <MyGrammarFactory.h>
#include <Grammar.h>
#include <TokenStream.h>
#include <SyntaxDirectedParser.h>
#include <FirstNFollowFactory.h>
#include <Lexer.h>
#include <LexerInputBuffer.h>
#include <memory>
#include <sstream>

using namespace JustCompiler::SyntacticAnalyzer::ContextFreeGrammar;
using namespace JustCompiler::SyntacticAnalyzer;
using namespace JustCompiler::ParserGrammar;
using namespace JustCompiler::LexicalAnalyzer;
using namespace std;

struct MyGrammarParserFixture {
    MyGrammarParserFixture() {
        Grammar grammar = MyGrammarFactory::CreateGrammar();
        PFirstFunction pFirst = FirstNFollowFactory::GetFirst(grammar);
        PFollowFunction pFollow = FirstNFollowFactory::GetFollow(grammar, pFirst);
        ParserTable parserTable(grammar, *pFirst, *pFollow);

        parser.reset(new SyntaxDirectedParser(grammar, parserTable));
    }

    virtual ~MyGrammarParserFixture() {};

    void Tokenize(const wstring& input) {
        auto_ptr<Lexer> lexer = MyGrammar::CreateLexer();

        wistringstream inputStream(input);
        auto_ptr<IInputBuffer> inputBuffer(new LexerInputBuffer(inputStream));
        lexer->SetInput(inputBuffer);

        LexerOutput lexerOutput = lexer->Tokenize();

        tokens = lexerOutput.get<0>();
        lexicalErrors = lexerOutput.get<1>();

        tokens.push_back(PToken(new Token(SpecialTokenTag::Eof)));

        tokenStream.reset(new TokenStream(tokens));
    }

    vector<PToken> tokens;
    vector<PLexicalError> lexicalErrors;
    std::auto_ptr<IParser> parser;
    boost::shared_ptr<ITokenStream> tokenStream;
};

BOOST_FIXTURE_TEST_SUITE( MyGrammarParserTestSuite, MyGrammarParserFixture )

BOOST_AUTO_TEST_CASE( MyGrammar_Valid ) {
    Tokenize(
        L"program first\n \
        var\n \
            a, b, c:integer\n \
        begin\n \
            read(a);\n \
            read(b);\n \
            c := a + b; \
            write(c)\n \
        end");

    BOOST_ASSERT(lexicalErrors.size() == 0);
    auto_ptr<ParserOutput> parserOutput = parser->Parse(tokenStream);

    BOOST_CHECK(parserOutput->errors.size() == 0);
}

BOOST_AUTO_TEST_CASE( MyGrammar_Valid2 ) {
    Tokenize(
        L"program first\n \
        var\n \
            a, b, c:integer\n \
        begin\n \
            read(a);\n \
            read(b);\n \
            c := (a + b) * b + a - (a + b * c);\n \
            write(c + b - a)\n \
        end");

    BOOST_ASSERT(lexicalErrors.size() == 0);
    auto_ptr<ParserOutput> parserOutput = parser->Parse(tokenStream);

    BOOST_CHECK(parserOutput->errors.size() == 0);
}

BOOST_AUTO_TEST_CASE( MyGrammar_Valid3 ) {
    Tokenize(
        L"program first\n \
        var\n \
            a, b, c:integer\n \
        begin\n \
            read(a);\n \
            read(b);\n \
            c := (a + b) * b + a - (a + b * c + 2.0);\n \
            write(c + b - a + 1)\n \
        end");

    BOOST_ASSERT(lexicalErrors.size() == 0);
    auto_ptr<ParserOutput> parserOutput = parser->Parse(tokenStream);

    BOOST_CHECK(parserOutput->errors.size() == 0);
}

BOOST_AUTO_TEST_CASE( MyGrammar_Valid4 ) {
    Tokenize(
        L"program first\n \
        var\n \
            a, b, c:integer;\n \
            d, e, f:real \
        begin\n \
            read(a, b, c, d, e, f);\n \
            f := a + b * c / d; \n \
            write(f)\n \
        end");

    BOOST_ASSERT(lexicalErrors.size() == 0);
    auto_ptr<ParserOutput> parserOutput = parser->Parse(tokenStream);

    BOOST_CHECK(parserOutput->errors.size() == 0);
}

BOOST_AUTO_TEST_CASE( MyGrammar_Valid5 ) {
    Tokenize(
        L"program first\n \
        var\n \
            a, b, c:integer;\n \
            d, e, f:real\n \
        begin\n \
            read(a, b, c, d, e, f);\n \
            f := a + b * c / d; \n \
            if f > 0 then \
                write(f)\n \
        end");

    BOOST_ASSERT(lexicalErrors.size() == 0);
    auto_ptr<ParserOutput> parserOutput = parser->Parse(tokenStream);

    BOOST_CHECK(parserOutput->errors.size() == 0);
}

BOOST_AUTO_TEST_CASE( MyGrammar_Valid6 ) {
    Tokenize(
        L"program first\n \
        var\n \
            a, b, c:integer;\n \
            d, e, f:real\n \
        begin\n \
            read(a, b, c, d, e, f);\n \
            f := sqrt(a + b * c / d); \n \
            if f > 0 then \
                write(f)\n \
        end");

    BOOST_ASSERT(lexicalErrors.size() == 0);
    auto_ptr<ParserOutput> parserOutput = parser->Parse(tokenStream);

    BOOST_CHECK(parserOutput->errors.size() == 0);
}

BOOST_AUTO_TEST_SUITE_END()