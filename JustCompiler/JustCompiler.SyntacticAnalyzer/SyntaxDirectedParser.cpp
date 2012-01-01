#include "SyntaxDirectedParser.h"
#include "TokenExpected.h"
#include "UnexpectedToken.h"
#include <SpecialTokenTag.h>
#include <assert.h>

using namespace JustCompiler::SyntacticAnalyzer::ContextFreeGrammar;
using namespace JustCompiler::LexicalAnalyzer;
using namespace JustCompiler::SyntacticAnalyzer::Errors;
using namespace std;

namespace JustCompiler {
namespace SyntacticAnalyzer {

    SyntaxDirectedParser::SyntaxDirectedParser(
        const Grammar& grammar,
        const ParserTable& parserTable)
        :grammar(grammar), parserTable(parserTable) {}

    auto_ptr<ParserOutput> SyntaxDirectedParser::Parse(boost::shared_ptr<ITokenStream> tokenStream) {
        PTerminal eofTerminal(new Terminal(SpecialTokenTag::Eof));
        PParseTreeNode root(new ParseTreeNode(grammar.StartSymbol()));

        auto_ptr<ParserOutput> output(new ParserOutput(root));

        while (!parserStack.empty()) {
            parserStack.pop();
        }
        
        parserStack.push(PParseTreeNode(new ParseTreeNode(eofTerminal)));
        parserStack.push(root);

        while (true) {
            PParseTreeNode currentNode = parserStack.top();
            PSymbol top = currentNode->GetSymbol();
            PToken inputToken = tokenStream->Peak();

            if (top->GetType() == SymbolType::Terminal) {
                PTerminal topAsTerm = boost::dynamic_pointer_cast<Terminal, Symbol>(top);
                assert(topAsTerm.get() != NULL);

                if (topAsTerm->GetTokenTag() == inputToken->GetTag()) {
                    if (topAsTerm->GetTokenTag() == SpecialTokenTag::Eof) {
                        //success
                        return output;
                    }
                    else {
                        //TODO: seems to be a workaround
                        currentNode->SetToken(inputToken);

                        parserStack.pop();
                        tokenStream->MoveForward();
                    }
                }
                else {
                    if (inputToken->GetTag() == SpecialTokenTag::Unrecognized) {
                        //recover from error in lexical analysis
                        parserStack.pop();
                        tokenStream->MoveForward();
                    }
                    else if (inputToken->GetTag() == SpecialTokenTag::Eof) {
                        //waited for terminal, encountered end of token stream => report error
                        output->errors.push_back(boost::shared_ptr<SyntaxError>(new SyntaxError(
                            tokenStream->LineNum(),
                            tokenStream->CharNum(),
                            ErrorClass::UnexpectedEndOfFile)));

                        return output;
                    }
                    else {
                        //invalid token
                        output->errors.push_back(boost::shared_ptr<TokenExpected>(new TokenExpected(
                            tokenStream->LineNum(),
                            tokenStream->CharNum(),
                            topAsTerm->GetTokenTag())));

                        return output;
                    }
                }
            }
            else {
                //non terminal
                PNonTerminal topAsNonTerm = boost::dynamic_pointer_cast<NonTerminal, Symbol>(top);
                NonTerminal* ptr = topAsNonTerm.get();
                
                
                assert(topAsNonTerm.get() != NULL);

                ParserTableEntry controlTableEntry = parserTable.GetEntry(topAsNonTerm->GetTag(), inputToken->GetTag());

                if (!controlTableEntry.IsError()) {
                    const Production* production = controlTableEntry.GetProduction();
                    assert(production != NULL);

                    //replace current non terminal on the top of the stack with the right part of selected production
                    parserStack.pop();

                    SymbolString prodRight = production->Right();
                    vector<PParseTreeNode> childTreeNodes;

                    SymbolString::const_iterator rightIt;
                    for (rightIt = prodRight.cbegin(); rightIt != prodRight.cend(); ++rightIt) {
                        PParseTreeNode childNode(new ParseTreeNode(*rightIt));

                        //build parse tree
                        currentNode->AddChildNode(childNode);
                        childTreeNodes.push_back(childNode);
                    }

                    for (int i = childTreeNodes.size() - 1; i >= 0; --i) {
                        //don't add empty symbol to the stack!
                        if (childTreeNodes[i]->GetSymbol()->GetType() == SymbolType::Terminal) {
                            PTerminal terminal = boost::dynamic_pointer_cast<Terminal, Symbol>(childTreeNodes[i]->GetSymbol());
                            assert(terminal.get() != NULL);

                            if (terminal->GetTokenTag() != SpecialTokenTag::Empty) {
                                parserStack.push(childTreeNodes[i]);
                            }
                        }
                        else {
                            parserStack.push(childTreeNodes[i]);
                        }
                    }
                }
                else {
                    //there's no entry in the parser table for such configuration

                    if (inputToken->GetTag() == SpecialTokenTag::Eof) {
                        output->errors.push_back(boost::shared_ptr<SyntaxError>(new SyntaxError(
                            tokenStream->LineNum(),
                            tokenStream->CharNum(),
                            ErrorClass::UnexpectedEndOfFile)));
                    }
                    else {
                        output->errors.push_back(boost::shared_ptr<UnexpectedToken>(new UnexpectedToken(
                            tokenStream->LineNum(),
                            tokenStream->CharNum(),
                            inputToken,
                            parserTable.GetExpectedTerminals(topAsNonTerm->GetTag()))));
                    }

                    return output;
                }
            }
        }
    }

}
}