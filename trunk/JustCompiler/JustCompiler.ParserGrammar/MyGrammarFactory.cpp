#include "MyGrammarFactory.h"
#include <vector>
#include <SpecialTokenTag.h>
#include "NonTerminalTag.h"
#include <TokenTag.h>
#include <iostream>
#include <iterator>
#include <sstream>
#include "TerminalWithDesc.h"
#include "NonTerminalWithDesc.h"

using namespace JustCompiler::SyntacticAnalyzer::ContextFreeGrammar;
using namespace JustCompiler::LexicalAnalyzer;
using namespace std;

namespace JustCompiler {
namespace ParserGrammar {

    Grammar MyGrammarFactory::CreateGrammar() {
        Grammar grammar;
        CreateNonTerminals(grammar);
        CreateTerminals(grammar);
        
        //creating the PASCAL grammar

        AddProduction("<prog>", "program id var <dec-list> begin <stmt-list> end", grammar);
        AddProduction("<dec-list>", "<dec> <dec-list'>", grammar);
        AddProduction("<dec-list'>", "; <dec> <dec-list'>", grammar);
        AddProduction("<dec-list'>", "empty", grammar);
        AddProduction("<dec>", "<id-list> : <type>", grammar);
        AddProduction("<id-list>", "id <id-list'>", grammar);
        AddProduction("<id-list'>", ", id <id-list'>", grammar);
        AddProduction("<id-list'>", "empty", grammar);
        AddProduction("<type>", "integer", grammar);
        AddProduction("<type>", "real", grammar);
        AddProduction("<stmt-list>", "<stmt> <stmt-list'>", grammar);
        AddProduction("<stmt-list'>", "; <stmt> <stmt-list'>", grammar);
        AddProduction("<stmt-list'>", "empty", grammar);
        AddProduction("<stmt>", "<assign>", grammar);
        AddProduction("<stmt>", "<read>", grammar);
        AddProduction("<stmt>", "<write>", grammar);
        AddProduction("<stmt>", "<for>", grammar);
        AddProduction("<stmt>", "<if-then-else>", grammar);
        AddProduction("<assign>", "id : = <E>", grammar);
        AddProduction("<read>", "read ( id )", grammar);
        AddProduction("<write>", "write ( <param-list> )", grammar);
        AddProduction("<for>", "for <index-exp> do <body>", grammar);
        AddProduction("<index-exp>", "<assign> to <E>", grammar);
        AddProduction("<body>", "<stmt>", grammar);
        AddProduction("<body>", "begin <stmt-list> end", grammar);
        AddProduction("<if-then-else>", "if <bool-E> then <body> <else>", grammar);
        AddProduction("<else>", "empty", grammar);
        AddProduction("<else>", "else <body>", grammar);
        AddProduction("<funcall>", "st-func ( <param-list> )", grammar);

        //expressions
        AddProduction("<E>", "<T> <E1>", grammar);
        AddProduction("<E1>", "+ <T> <E1>", grammar);
        AddProduction("<E1>", "- <T> <E1>", grammar);
        AddProduction("<E1>", "empty", grammar);
        AddProduction("<T>", "<F> <T1>", grammar);
        AddProduction("<T1>", "* <F> <T1>", grammar);
        AddProduction("<T1>", "/ <F> <T1>", grammar);
        AddProduction("<T1>", "empty", grammar);
        AddProduction("<F>", "( <E> )", grammar);
        AddProduction("<F>", "id", grammar);
        AddProduction("<F>", "int-const", grammar);
        AddProduction("<F>", "real-const", grammar);
        AddProduction("<F>", "<funcall>", grammar);
        AddProduction("<param-list>", "<param> <param-list'>", grammar);
        AddProduction("<param-list'>", ", <param> <param-list'>", grammar);
        AddProduction("<param-list'>", "empty", grammar);
        AddProduction("<param>", "<E>", grammar);

        //boolean expressions
        AddProduction("<bool-E>", "<E> <bool-E'>", grammar);
        AddProduction("<bool-E'>", "< <E>", grammar);
        AddProduction("<bool-E'>", "> <E>", grammar);
        AddProduction("<bool-E'>", "= <E>", grammar);

        grammar.SetStartSymbol(grammar.N("<prog>"));

        return grammar;
    }

    Production& MyGrammarFactory::AddProduction(const string& left, const string& right, Grammar& grammar) {
        vector<string> rightNames;
        istringstream iss(right);

        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(rightNames));

        PNonTerminal leftNonTerm = boost::dynamic_pointer_cast<NonTerminal, Symbol>(GetSymbol(left, grammar));
        assert(leftNonTerm.get() != NULL);

        SymbolString rightSymbols;

        vector<string>::const_iterator rightIt;
        for (rightIt = rightNames.cbegin(); rightIt != rightNames.cend(); ++rightIt) {
            PSymbol sym = GetSymbol(*rightIt, grammar);
            assert(sym.get() != NULL);
            rightSymbols.push_back(sym);
        }

        return grammar.AddProduction(Production(leftNonTerm, rightSymbols));
    }

    PSymbol MyGrammarFactory::GetSymbol(const string& name, const Grammar& grammar) {
        if (name.length() > 1 && name[0] == '<' && name[name.length() - 1] == '>') {
            //non terminal
            return grammar.N(name);
        }
        else {
            return grammar.T(name);
        }
    }

    void MyGrammarFactory::CreateNonTerminals(Grammar& grammar) {
        AddNonTerminal("<prog>", NonTerminalTag::Prog, grammar);
        AddNonTerminal("<dec-list>", NonTerminalTag::DecList, grammar);
        AddNonTerminal("<dec-list'>", NonTerminalTag::DecListStroke, grammar);
        AddNonTerminal("<dec>", NonTerminalTag::Dec, grammar);
        AddNonTerminal("<id-list>", NonTerminalTag::IdList, grammar);
        AddNonTerminal("<id-list'>", NonTerminalTag::IdListStroke, grammar);
        AddNonTerminal("<type>", NonTerminalTag::Type, grammar);
        AddNonTerminal("<stmt-list>", NonTerminalTag::StmtList, grammar);
        AddNonTerminal("<stmt-list'>", NonTerminalTag::StmtListStroke, grammar);
        AddNonTerminal("<stmt>", NonTerminalTag::Stmt, grammar);
        AddNonTerminal("<assign>", NonTerminalTag::Assign, grammar);
        AddNonTerminal("<read>", NonTerminalTag::Read, grammar);
        AddNonTerminal("<write>", NonTerminalTag::Write, grammar);
        AddNonTerminal("<for>", NonTerminalTag::For, grammar);
        AddNonTerminal("<index-exp>", NonTerminalTag::IndexExp, grammar);
        AddNonTerminal("<body>", NonTerminalTag::Body, grammar);
        AddNonTerminal("<if-then-else>", NonTerminalTag::IfThenElse, grammar);
        AddNonTerminal("<if-then>", NonTerminalTag::IfThen, grammar);
        AddNonTerminal("<else>", NonTerminalTag::Else, grammar);
        AddNonTerminal("<goto>", NonTerminalTag::Goto, grammar);
        AddNonTerminal("<E>", NonTerminalTag::Expression, grammar);
        AddNonTerminal("<T>", NonTerminalTag::Term, grammar);
        AddNonTerminal("<E1>", NonTerminalTag::ExpressionStroke, grammar);
        AddNonTerminal("<T1>", NonTerminalTag::TermStroke, grammar);
        AddNonTerminal("<F>", NonTerminalTag::Factor, grammar);
        AddNonTerminal("<bool-E>", NonTerminalTag::BooleanExpression, grammar);
        AddNonTerminal("<bool-E'>", NonTerminalTag::BooleanExpressionStroke, grammar);
        AddNonTerminal("<funcall>", NonTerminalTag::FunctionCall, grammar);
        AddNonTerminal("<param-list>", NonTerminalTag::ParamList, grammar);
        AddNonTerminal("<param-list'>", NonTerminalTag::ParamListStroke, grammar);
        AddNonTerminal("<param>", NonTerminalTag::Param, grammar);
    }

    void MyGrammarFactory::CreateTerminals(Grammar& grammar) {
        AddTerminal("program", TokenTag::Program, grammar);
        AddTerminal("id", TokenTag::Identifier, grammar);
        AddTerminal("var", TokenTag::Var, grammar);
        AddTerminal("begin", TokenTag::Begin, grammar);
        AddTerminal("end", TokenTag::End, grammar);
        AddTerminal(";", TokenTag::Semicolon, grammar);
        AddTerminal("empty", SpecialTokenTag::Empty, grammar);
        AddTerminal(":", TokenTag::Colon, grammar);
        AddTerminal(",", TokenTag::Comma, grammar);
        AddTerminal("integer", TokenTag::Type_Int, grammar);
        AddTerminal("real", TokenTag::Type_Real, grammar);
        AddTerminal("=", TokenTag::Equals, grammar);
        AddTerminal("read", TokenTag::Read, grammar);
        AddTerminal("(", TokenTag::OpeningRoundBracket, grammar);
        AddTerminal(")", TokenTag::ClosingRoundBracket, grammar);
        AddTerminal("write", TokenTag::Write, grammar);
        AddTerminal("for", TokenTag::For, grammar);
        AddTerminal("do", TokenTag::Do, grammar);
        AddTerminal("to", TokenTag::To, grammar);
        AddTerminal("if", TokenTag::If, grammar);
        AddTerminal("then", TokenTag::Then, grammar);
        AddTerminal("else", TokenTag::Else, grammar);
        AddTerminal("+", TokenTag::Plus, grammar);
        AddTerminal("-", TokenTag::Minus, grammar);
        AddTerminal("*", TokenTag::Asterisk, grammar);
        AddTerminal("/", TokenTag::Slash, grammar);
        AddTerminal("int-const", TokenTag::IntConstant, grammar);
        AddTerminal("real-const", TokenTag::RealConstant, grammar);
        AddTerminal("goto", TokenTag::Goto, grammar);
        AddTerminal("st-func", TokenTag::StandardFunction, grammar);
        AddTerminal("<", TokenTag::LessThan, grammar);
        AddTerminal(">", TokenTag::GreaterThan, grammar);
    }

    void MyGrammarFactory::AddTerminal(const string& name, int tokenTag, Grammar& grammar) {
        PTerminal terminal(new TerminalWithDesc(tokenTag, name));

        grammar.AddTerminal(name, terminal);
    }

    void MyGrammarFactory::AddNonTerminal(const string& name, int tag, Grammar& grammar) {
        PNonTerminal nonTerm(new NonTerminalWithDesc(tag, name));

        grammar.AddNonTerminal(name, nonTerm);
    }
}
}