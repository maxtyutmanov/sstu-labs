#include "SemanticChecker.h"
#include <NonTerminalTag.h>
#include <TokenTag.h>
#include "Redefinition.h"
#include "UndeclaredIdentifier.h"
#include <NodeSearchPredicates.h>

using namespace std;
using namespace JustCompiler::SyntacticAnalyzer;
using namespace JustCompiler::LexicalAnalyzer;
using namespace JustCompiler::LexicalAnalyzer::Tokens;
using namespace JustCompiler::SyntacticAnalyzer::ContextFreeGrammar;
using namespace JustCompiler::ParserGrammar;
using namespace JustCompiler::SemanticAnalyzer::Errors;

namespace JustCompiler {
namespace SemanticAnalyzer {

    SemanticCheckerOutput SemanticChecker::Check(const ParseTree parseTree) {
        SemanticCheckerOutput output;
        output.symbolTable = CreateSymbolTable(parseTree, output);

        FindUndeclaredIdentifiers(parseTree, output);

        return output;
    }

    PSymbolTable SemanticChecker::CreateSymbolTable(const ParseTree parseTree, SemanticCheckerOutput& output) {
        vector<PParseTreeNode> decs = parseTree.GetRoot()->GetChildren(NonTerminalTagPredicate(NonTerminalTag::Dec), true);

        PSymbolTable symTable(new SymbolTable());

        for (size_t i = 0; i < decs.size(); ++i) {
            vector<PParseTreeNode> ids = decs[i]->GetChildren(TerminalTagPredicate(TokenTag::Identifier), true);

            for (size_t j = 0; j < ids.size(); ++j) {
                PToken token = ids[j]->GetToken();
                assert(token.get() != NULL);
                PIdentifier identifier = boost::dynamic_pointer_cast<Identifier, Token>(token);
                assert(identifier.get() != NULL);

                if (symTable->HasEntry(identifier->GetName())) {
                    output.errors.push_back(PRedefinition(new Redefinition(identifier->GetLineNum(), identifier->GetCharNum(), identifier)));
                }
                else {
                    symTable->AddEntry(identifier);
                }
            }
        }

        return symTable;
    }

    void SemanticChecker::FindUndeclaredIdentifiers(const ParseTree parseTree, SemanticCheckerOutput& output) {
        vector<PParseTreeNode> mainStmtListVector = parseTree.GetRoot()->GetChildren(NonTerminalTagPredicate(NonTerminalTag::StmtList), false);
        assert(mainStmtListVector.size() == 1);
        PParseTreeNode programStmtList = mainStmtListVector[0];

        vector<PParseTreeNode> identifiers = programStmtList->GetChildren(TerminalTagPredicate(TokenTag::Identifier), true);

        for (size_t i = 0; i < identifiers.size(); ++i) {
            PToken token = identifiers[i]->GetToken();
            assert(token.get() != NULL);
            PIdentifier id = boost::dynamic_pointer_cast<Identifier, Token>(token);
            assert(id.get() != NULL);

            if (!output.symbolTable->HasEntry(id->GetName())) {
                output.errors.push_back(PUndeclaredIdentifier(new UndeclaredIdentifier(id->GetLineNum(), id->GetCharNum(), id)));
            }
        }
    }

    /*bool SemanticChecker::IsDeclaration(const PParseTreeNode node) {
        if (node->GetSymbol()->GetType() == SymbolType::NonTerminal) {
            PNonTerminal dec = boost::dynamic_pointer_cast<NonTerminal, Symbol>(node->GetSymbol());
            assert(dec.get() != NULL);

            return dec->GetTag() == NonTerminalTag::Dec;
        }
        else {
            return false;
        }
    }

    bool SemanticChecker::IsIdentifier(const SyntacticAnalyzer::PParseTreeNode node) {
        if (node->GetSymbol()->GetType() == SymbolType::Terminal) {
            PTerminal term = boost::dynamic_pointer_cast<Terminal, Symbol>(node->GetSymbol());
            assert(term.get() != NULL);

            return term->GetTokenTag() == TokenTag::Identifier;
        }
        else {
            return false;
        }
    }

    bool SemanticChecker::IsStmtList(const SyntacticAnalyzer::PParseTreeNode node) {
        if (node->GetSymbol()->GetType() == SymbolType::NonTerminal) {
            PNonTerminal nt = boost::dynamic_pointer_cast<NonTerminal, Symbol>(node->GetSymbol());
            assert(nt.get() != NULL);

            return nt->GetTag() == NonTerminalTag::StmtList;
        }
        else {
            return false;
        }
    }*/
}
}