#include "TestGrammarFactory.h"

#include <vector>
#include <SpecialTokenTag.h>
#include <NonTerminalTag.h>
#include <TokenTag.h>

using namespace JustCompiler::SyntacticAnalyzer::ContextFreeGrammar;
using namespace JustCompiler::LexicalAnalyzer;
using namespace JustCompiler::ParserGrammar;
using namespace std;

namespace JustCompiler {
namespace Tests {

    Grammar TestGrammarFactory::CreateExpressionsGrammar() {
        Grammar grammar;
        CreateNonTerminals(grammar);
        CreateTerminals(grammar);
        ArithmeticExpressions(grammar);
        grammar.SetStartSymbol(grammar.N("E"));

        return grammar;
    }

    void TestGrammarFactory::ArithmeticExpressions(Grammar& grammar) {

        //E->TE'
        SymbolString TE1;
        TE1.push_back(grammar.N("T"));
        TE1.push_back(grammar.N("E1"));
        grammar.AddProduction(Production(grammar.N("E"), TE1));
        
        //E'->+TE'
        SymbolString plusTE1;
        plusTE1.push_back(grammar.T("+"));
        plusTE1.push_back(grammar.N("T"));
        plusTE1.push_back(grammar.N("E1"));
        grammar.AddProduction(Production(grammar.N("E1"), plusTE1));

        //E'->-TE'
        SymbolString minusTE1;
        minusTE1.push_back(grammar.T("-"));
        minusTE1.push_back(grammar.N("T"));
        minusTE1.push_back(grammar.N("E1"));
        grammar.AddProduction(Production(grammar.N("E1"), minusTE1));

        //E'->empty
        grammar.AddProduction(Production(grammar.N("E1"), grammar.T("empty")));

        //T->FT'
        SymbolString FT1;
        FT1.push_back(grammar.N("F"));
        FT1.push_back(grammar.N("T1"));
        grammar.AddProduction(Production(grammar.N("T"), FT1));

        //T'->*FT'
        SymbolString asteriskFT1;
        asteriskFT1.push_back(grammar.T("*"));
        asteriskFT1.push_back(grammar.N("F"));
        asteriskFT1.push_back(grammar.N("T1"));
        grammar.AddProduction(Production(grammar.N("T1"), asteriskFT1));

        //T'->/FT'
        SymbolString slashFT1;
        slashFT1.push_back(grammar.T("/"));
        slashFT1.push_back(grammar.N("F"));
        slashFT1.push_back(grammar.N("T1"));
        grammar.AddProduction(Production(grammar.N("T1"), slashFT1));

        //T'->empty
        grammar.AddProduction(Production(grammar.N("T1"), grammar.T("empty")));

        //F->(E)
        SymbolString lbracketErbracket;
        lbracketErbracket.push_back(grammar.T("("));
        lbracketErbracket.push_back(grammar.N("E"));
        lbracketErbracket.push_back(grammar.T(")"));
        grammar.AddProduction(Production(grammar.N("F"), lbracketErbracket));

        //F->id
        grammar.AddProduction(Production(grammar.N("F"), grammar.T("id")));
    }

    void TestGrammarFactory::CreateNonTerminals(Grammar& grammar) {
        PNonTerminal E(new NonTerminal(NonTerminalTag::Expression));
        grammar.AddNonTerminal("E", E);
        PNonTerminal T(new NonTerminal(NonTerminalTag::Term));
        grammar.AddNonTerminal("T", T);
        PNonTerminal E1(new NonTerminal(NonTerminalTag::ExpressionStroke));
        grammar.AddNonTerminal("E1", E1);
        PNonTerminal T1(new NonTerminal(NonTerminalTag::TermStroke));
        grammar.AddNonTerminal("T1", T1);
        PNonTerminal F(new NonTerminal(NonTerminalTag::Factor));
        grammar.AddNonTerminal("F", F);
    }

    void TestGrammarFactory::CreateTerminals(Grammar& grammar) {
        PTerminal plus(new Terminal(TokenTag::Plus));
        grammar.AddTerminal("+", plus);
        PTerminal minus(new Terminal(TokenTag::Minus));
        grammar.AddTerminal("-", minus);
        PTerminal empty(new Terminal(SpecialTokenTag::Empty));
        grammar.AddTerminal("empty", empty);
        PTerminal asterisk(new Terminal(TokenTag::Asterisk));
        grammar.AddTerminal("*", asterisk);
        PTerminal slash(new Terminal(TokenTag::Slash));
        grammar.AddTerminal("/", slash);
        PTerminal lbracket(new Terminal(TokenTag::OpeningRoundBracket));
        grammar.AddTerminal("(", lbracket);
        PTerminal rbracket(new Terminal(TokenTag::ClosingRoundBracket));
        grammar.AddTerminal(")", rbracket);
        PTerminal id(new Terminal(TokenTag::Identifier));
        grammar.AddTerminal("id", id);
    }
}
}