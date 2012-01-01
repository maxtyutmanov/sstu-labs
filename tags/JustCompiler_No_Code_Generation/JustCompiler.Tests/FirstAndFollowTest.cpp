#include <boost/test/auto_unit_test.hpp>
#include <FirstFunction.h>
#include <FollowFunction.h>
#include <Terminal.h>
#include <NonTerminal.h>
#include <FirstNFollowFactory.h>
#include <TokenTag.h>
#include <ParserTable.h>
#include <NonTerminalTag.h>
#include "TestGrammarFactory.h"

using namespace JustCompiler::SyntacticAnalyzer::ContextFreeGrammar;
using namespace JustCompiler::ParserGrammar;
using namespace JustCompiler::Tests;

struct ArithmeticExprFNFFixture {
    virtual ~ArithmeticExprFNFFixture() {}

    ArithmeticExprFNFFixture() {
        exprGrammar = TestGrammarFactory::CreateExpressionsGrammar();
    }

    Grammar exprGrammar;
};

BOOST_FIXTURE_TEST_SUITE( FirstNFollowExpressionGrammarSuite, ArithmeticExprFNFFixture )

BOOST_AUTO_TEST_CASE( FirstFunctionTest ) {
    SymbolString str1;
    str1.push_back(PTerminal(new Terminal(1)));
    str1.push_back(PNonTerminal(new NonTerminal(1)));

    SymbolString str2;
    str2.push_back(PTerminal(new Terminal(1)));
    str2.push_back(PTerminal(new Terminal(1)));
    
    FirstFunction first;

    first(str1).push_back(PTerminal(new Terminal(2)));
    first(str1).push_back(PTerminal(new Terminal(3)));
    first(str2).push_back(PTerminal(new Terminal(2)));

    BOOST_CHECK(first(str1).size() == 2);
    BOOST_CHECK(first(str2).size() == 1);
}

BOOST_AUTO_TEST_CASE( FollowFunctionTest ) {
    PNonTerminal s1(new NonTerminal(1));
    PNonTerminal s2(new NonTerminal(2));

    FollowFunction follow;

    follow(s1).push_back(PTerminal(new Terminal(2)));
    follow(s1).push_back(PTerminal(new Terminal(3)));
    follow(s2).push_back(PTerminal(new Terminal(2)));

    BOOST_CHECK(follow(s1).size() == 2);
    BOOST_CHECK(follow(s2).size() == 1);
}

BOOST_AUTO_TEST_CASE( FirstFunction_ArithmeticExpressions ) {
    PFirstFunction pFirst = FirstNFollowFactory::GetFirst(exprGrammar);
    FirstFunction& first = *pFirst;

    TerminalSet f_E = first(exprGrammar.N("E"));
    BOOST_ASSERT(f_E.size() == 2);
    BOOST_CHECK(f_E.Contains(TokenTag::OpeningRoundBracket));
    BOOST_CHECK(f_E.Contains(TokenTag::Identifier));

    TerminalSet f_T = first(exprGrammar.N("T"));
    BOOST_ASSERT(f_T.size() == 2);
    BOOST_CHECK(f_T.Contains(TokenTag::OpeningRoundBracket));
    BOOST_CHECK(f_T.Contains(TokenTag::Identifier));

    TerminalSet f_F = first(exprGrammar.N("F"));
    BOOST_ASSERT(f_F.size() == 2);
    BOOST_CHECK(f_F.Contains(TokenTag::OpeningRoundBracket));
    BOOST_CHECK(f_F.Contains(TokenTag::Identifier));

    TerminalSet f_E1 = first(exprGrammar.N("E1"));
    BOOST_ASSERT(f_E1.size() == 3);
    BOOST_CHECK(f_E1.Contains(TokenTag::Plus));
    BOOST_CHECK(f_E1.Contains(SpecialTokenTag::Empty));
    BOOST_CHECK(f_E1.Contains(TokenTag::Minus));

    TerminalSet f_T1 = first(exprGrammar.N("T1"));
    BOOST_ASSERT(f_T1.size() == 3);
    BOOST_CHECK(f_T1.Contains(TokenTag::Asterisk));
    BOOST_CHECK(f_T1.Contains(TokenTag::Slash));
    BOOST_CHECK(f_T1.Contains(SpecialTokenTag::Empty));
}

BOOST_AUTO_TEST_CASE( FollowFunction_ArithmeticExpressions ) {
    PFirstFunction pFirst = FirstNFollowFactory::GetFirst(exprGrammar);

    PFollowFunction pFollow = FirstNFollowFactory::GetFollow(exprGrammar, pFirst);

    FollowFunction& follow = *pFollow;

    TerminalSet f_E = follow(exprGrammar.N("E"));
    BOOST_ASSERT(f_E.size() == 2);
    BOOST_CHECK(f_E.Contains(TokenTag::ClosingRoundBracket));
    BOOST_CHECK(f_E.Contains(SpecialTokenTag::Eof));

    TerminalSet f_E1 = follow(exprGrammar.N("E1"));
    BOOST_ASSERT(f_E1.size() == 2);
    BOOST_CHECK(f_E1.Contains(TokenTag::ClosingRoundBracket));
    BOOST_CHECK(f_E1.Contains(SpecialTokenTag::Eof));

    TerminalSet f_T = follow(exprGrammar.N("T"));
    BOOST_ASSERT(f_T.size() == 4);
    BOOST_CHECK(f_T.Contains(TokenTag::Plus));
    BOOST_CHECK(f_T.Contains(TokenTag::Minus));
    BOOST_CHECK(f_T.Contains(TokenTag::ClosingRoundBracket));
    BOOST_CHECK(f_T.Contains(SpecialTokenTag::Eof));

    TerminalSet f_T1 = follow(exprGrammar.N("T1"));
    BOOST_ASSERT(f_T1.size() == 4);
    BOOST_CHECK(f_T1.Contains(TokenTag::Plus));
    BOOST_CHECK(f_T1.Contains(TokenTag::Minus));
    BOOST_CHECK(f_T1.Contains(TokenTag::ClosingRoundBracket));
    BOOST_CHECK(f_T1.Contains(SpecialTokenTag::Eof));

    TerminalSet f_F = follow(exprGrammar.N("F"));
    BOOST_ASSERT(f_F.size() == 6);
    BOOST_CHECK(f_F.Contains(TokenTag::Plus));
    BOOST_CHECK(f_F.Contains(TokenTag::Minus));
    BOOST_CHECK(f_F.Contains(TokenTag::Asterisk));
    BOOST_CHECK(f_F.Contains(TokenTag::Slash));
    BOOST_CHECK(f_F.Contains(TokenTag::ClosingRoundBracket));
    BOOST_CHECK(f_F.Contains(SpecialTokenTag::Eof));
}

BOOST_AUTO_TEST_CASE( ParserTable_ArithmeticExpressions ) {
    PFirstFunction pFirst = FirstNFollowFactory::GetFirst(exprGrammar);

    PFollowFunction pFollow = FirstNFollowFactory::GetFollow(exprGrammar, pFirst);

    ParserTable parserTable(exprGrammar, *pFirst, *pFollow);

    const Production* p1 = parserTable.GetEntry(exprGrammar.N("E")->GetTag(), TokenTag::Identifier).GetProduction();
    BOOST_ASSERT(p1 != NULL);
    BOOST_CHECK(p1->Left()->GetTag() == NonTerminalTag::Expression);
    BOOST_ASSERT(p1->Right().size() == 2);
    BOOST_CHECK(*p1->Right()[0] == *PNonTerminal(new NonTerminal(NonTerminalTag::Term)));
    BOOST_CHECK(*p1->Right()[1] == *PNonTerminal(new NonTerminal(NonTerminalTag::ExpressionStroke)));

    const Production* p2 = parserTable.GetEntry(exprGrammar.N("E")->GetTag(), TokenTag::OpeningRoundBracket).GetProduction();
    BOOST_ASSERT(p2 != NULL);
    BOOST_CHECK(p2->Left()->GetTag() == NonTerminalTag::Expression);
    BOOST_ASSERT(p2->Right().size() == 2);
    BOOST_CHECK(*p2->Right()[0] == *PNonTerminal(new NonTerminal(NonTerminalTag::Term)));
    BOOST_CHECK(*p2->Right()[1] == *PNonTerminal(new NonTerminal(NonTerminalTag::ExpressionStroke)));

    const Production* p3 = parserTable.GetEntry(exprGrammar.N("E1")->GetTag(), TokenTag::Plus).GetProduction();
    BOOST_ASSERT(p3 != NULL);
    BOOST_CHECK(p3->Left()->GetTag() == NonTerminalTag::ExpressionStroke);
    BOOST_ASSERT(p3->Right().size() == 3);
    BOOST_CHECK(*p3->Right()[0] == *PTerminal(new Terminal(TokenTag::Plus)));
    BOOST_CHECK(*p3->Right()[1] == *PNonTerminal(new NonTerminal(NonTerminalTag::Term)));
    BOOST_CHECK(*p3->Right()[2] == *PNonTerminal(new NonTerminal(NonTerminalTag::ExpressionStroke)));

    const Production* p4 = parserTable.GetEntry(exprGrammar.N("E1")->GetTag(), TokenTag::ClosingRoundBracket).GetProduction();
    BOOST_ASSERT(p4 != NULL);
    BOOST_CHECK(p4->Left()->GetTag() == NonTerminalTag::ExpressionStroke);
    BOOST_ASSERT(p4->Right().size() == 1);
    BOOST_CHECK(*p4->Right()[0] == *PTerminal(new Terminal(SpecialTokenTag::Empty)));

    const Production* p5 = parserTable.GetEntry(exprGrammar.N("E1")->GetTag(), SpecialTokenTag::Eof).GetProduction();
    BOOST_ASSERT(p5 != NULL);
    BOOST_CHECK(p5->Left()->GetTag() == NonTerminalTag::ExpressionStroke);
    BOOST_ASSERT(p5->Right().size() == 1);
    BOOST_CHECK(*p5->Right()[0] == *PTerminal(new Terminal(SpecialTokenTag::Empty)));

    const Production* p6 = parserTable.GetEntry(exprGrammar.N("T")->GetTag(), TokenTag::Identifier).GetProduction();
    BOOST_ASSERT(p6 != NULL);
    BOOST_CHECK(p6->Left()->GetTag() == NonTerminalTag::Term);
    BOOST_ASSERT(p6->Right().size() == 2);
    BOOST_CHECK(*p6->Right()[0] == *PNonTerminal(new NonTerminal(NonTerminalTag::Factor)));
    BOOST_CHECK(*p6->Right()[1] == *PNonTerminal(new NonTerminal(NonTerminalTag::TermStroke)));

    const Production* p7 = parserTable.GetEntry(exprGrammar.N("T")->GetTag(), TokenTag::OpeningRoundBracket).GetProduction();
    BOOST_ASSERT(p7 != NULL);
    BOOST_CHECK(p7->Left()->GetTag() == NonTerminalTag::Term);
    BOOST_ASSERT(p7->Right().size() == 2);
    BOOST_CHECK(*p7->Right()[0] == *PNonTerminal(new NonTerminal(NonTerminalTag::Factor)));
    BOOST_CHECK(*p7->Right()[1] == *PNonTerminal(new NonTerminal(NonTerminalTag::TermStroke)));

    const Production* p8 = parserTable.GetEntry(exprGrammar.N("T1")->GetTag(), TokenTag::Plus).GetProduction();
    BOOST_ASSERT(p8 != NULL);
    BOOST_CHECK(p8->Left()->GetTag() == NonTerminalTag::TermStroke);
    BOOST_ASSERT(p8->Right().size() == 1);
    BOOST_CHECK(*p8->Right()[0] == *PTerminal(new Terminal(SpecialTokenTag::Empty)));

    const Production* p9 = parserTable.GetEntry(exprGrammar.N("T1")->GetTag(), TokenTag::Asterisk).GetProduction();
    BOOST_ASSERT(p9 != NULL);
    BOOST_CHECK(p9->Left()->GetTag() == NonTerminalTag::TermStroke);
    BOOST_ASSERT(p9->Right().size() == 3);
    BOOST_CHECK(*p9->Right()[0] == *PTerminal(new Terminal(TokenTag::Asterisk)));
    BOOST_CHECK(*p9->Right()[1] == *PNonTerminal(new NonTerminal(NonTerminalTag::Factor)));
    BOOST_CHECK(*p9->Right()[2] == *PNonTerminal(new NonTerminal(NonTerminalTag::TermStroke)));

    const Production* p10 = parserTable.GetEntry(exprGrammar.N("T1")->GetTag(), TokenTag::ClosingRoundBracket).GetProduction();
    BOOST_ASSERT(p10 != NULL);
    BOOST_CHECK(p10->Left()->GetTag() == NonTerminalTag::TermStroke);
    BOOST_ASSERT(p10->Right().size() == 1);
    BOOST_CHECK(*p10->Right()[0] == *PTerminal(new Terminal(SpecialTokenTag::Empty)));

    const Production* p11 = parserTable.GetEntry(exprGrammar.N("T1")->GetTag(), SpecialTokenTag::Eof).GetProduction();
    BOOST_ASSERT(p11 != NULL);
    BOOST_CHECK(p11->Left()->GetTag() == NonTerminalTag::TermStroke);
    BOOST_ASSERT(p11->Right().size() == 1);
    BOOST_CHECK(*p11->Right()[0] == *PTerminal(new Terminal(SpecialTokenTag::Empty)));

    const Production* p12 = parserTable.GetEntry(exprGrammar.N("F")->GetTag(), TokenTag::Identifier).GetProduction();
    BOOST_ASSERT(p12 != NULL);
    BOOST_CHECK(p12->Left()->GetTag() == NonTerminalTag::Factor);
    BOOST_ASSERT(p12->Right().size() == 1);
    BOOST_CHECK(*p12->Right()[0] == *PTerminal(new Terminal(TokenTag::Identifier)));

    const Production* p13 = parserTable.GetEntry(exprGrammar.N("F")->GetTag(), TokenTag::OpeningRoundBracket).GetProduction();
    BOOST_CHECK(p13->Left()->GetTag() == NonTerminalTag::Factor);
    BOOST_ASSERT(p13->Right().size() == 3);
    BOOST_CHECK(*p13->Right()[0] == *PTerminal(new Terminal(TokenTag::OpeningRoundBracket)));
    BOOST_CHECK(*p13->Right()[1] == *PNonTerminal(new NonTerminal(NonTerminalTag::Expression)));
    BOOST_CHECK(*p13->Right()[2] == *PTerminal(new Terminal(TokenTag::ClosingRoundBracket)));
}

BOOST_AUTO_TEST_SUITE_END()