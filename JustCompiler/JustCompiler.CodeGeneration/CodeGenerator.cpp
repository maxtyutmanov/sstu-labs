#include "CodeGenerator.h"
#include <NodeSearchPredicates.h>
#include "ParseTreeDirectIterator.h"
#include "OperandAttribute.h"
#include "Variable.h"
#include <TokenTag.h>
#include <NonTerminalTag.h>
#include <Tokens.h>
#include <boost/lexical_cast.hpp>
#include <SpecialTokenTag.h>
#include <StandardFunction.h>

using namespace std;
using namespace JustCompiler::SyntacticAnalyzer;
using namespace JustCompiler::SemanticAnalyzer;
using namespace JustCompiler::LexicalAnalyzer;
using namespace JustCompiler::LexicalAnalyzer::Tokens;
using namespace JustCompiler::ParserGrammar;

namespace JustCompiler {
namespace CodeGeneration {

    CodeGenerator::CodeGenerator()
        : variablesCounter(0), labelsCounter(0) {}

    IntermediateCode CodeGenerator::GenerateCode(ParseTree& parseTree) {
        IntermediateCode code;

        ParseTreeDirectIterator it;
        vector<TraverseStepInfo> allNodes = it.Iterate(parseTree);

        for (size_t i = 0; i < allNodes.size(); ++i) {
            if (allNodes[i].stepType == TraverseStepType::TopDown) {
                TopDownProcess(allNodes[i].node, code);
            }
            else if (allNodes[i].stepType == TraverseStepType::BottomUp) {
                BottomUpProcess(allNodes[i].node, code);
            }
        }

        return code;
    }

    void CodeGenerator::TopDownProcess(PParseTreeNode node, IntermediateCode& code) {
        PSymbol symbol = node->GetSymbol();

        if (symbol->GetType() == SymbolType::NonTerminal && !node->IsEmpty()) {
            PNonTerminal nonTerminal = boost::dynamic_pointer_cast<NonTerminal, Symbol>(symbol);
            assert(nonTerminal.get() != NULL);

            if (nonTerminal->GetTag() == NonTerminalTag::IfThenElse) {
                SetEndBlockLabel(node, GetTmpLabel());

                PParseTreeNode elseBlock = node->FirstChild(NonTerminalTagPredicate(NonTerminalTag::Else));
                assert(elseBlock.get() != NULL);

                if (!elseBlock->IsEmpty()) {
                    SetBeginBlockLabel(elseBlock, GetTmpLabel());
                }
            }
            else if (nonTerminal->GetTag() == NonTerminalTag::Else) {
                POperand beginLbl = GetBeginBlockLabel(node);
                code.AddCommand(OpCode::LABEL, beginLbl, NULL, NULL);
            }
            else if (nonTerminal->GetTag() == NonTerminalTag::For) {
                SetEndBlockLabel(node, GetTmpLabel());

                PParseTreeNode indexExp = node->FirstChild(NonTerminalTagPredicate(NonTerminalTag::IndexExp));
                SetBeginBlockLabel(indexExp, GetTmpLabel());

                PParseTreeNode bodyExp = node->FirstChild(NonTerminalTagPredicate(NonTerminalTag::Body));
                SetBeginBlockLabel(bodyExp, GetTmpLabel());
            }
            //else if (nonTerminal->GetTag() == NonTerminalTag::IndexExp) {
            //    //POperandAttribute beginLblAttr = node->GetTypedAttribute<OperandAttribute>("begin_block_lbl");
            //    POperand beginLbl = GetBeginBlockLabel(node);

            //    code.AddCommand(OpCode::LABEL, beginLbl, NULL, NULL);
            //}
            /*else if (nonTerminal->GetTag() == NonTerminalTag::Body) {
                assert(node->Parent().get() != NULL);
                if (node->Parent()->Is(NonTerminalTagPredicate(NonTerminalTag::For))) {
                    POperand beginLbl = GetBeginBlockLabel(node);
                    code.AddCommand(OpCode::LABEL, beginLbl, NULL, NULL);
                }
            }*/
        }
        else if (!node->IsEmpty()) {
            PTerminal terminal = boost::dynamic_pointer_cast<Terminal, Symbol>(symbol);
            assert(terminal.get() != NULL);

            if (terminal->GetTokenTag() != SpecialTokenTag::Empty) {
                PToken token = node->GetToken();
                assert(token.get() != NULL);

                if (token->GetTag() == TokenTag::IntConstant) {
                    IntConstant* intConstant = (IntConstant*)(token.get());
                    POperand operand(new IntOperand(intConstant->GetValue()));
                    node->SetAttribute("value", POperandAttribute(new OperandAttribute(operand)));
                }
                else if (token->GetTag() == TokenTag::RealConstant) {
                    RealConstant* realConstant = (RealConstant*)(token.get());
                    POperand operand(new RealOperand(realConstant->GetValue()));
                    node->SetAttribute("value", POperandAttribute(new OperandAttribute(operand)));
                }
                else if (token->GetTag() == TokenTag::Identifier) {
                    Identifier* id = (Identifier*)(token.get());
                    Variable variable(id->GetName());
                    POperand operand(new VariableOperand(variable));
                    node->SetAttribute("value", POperandAttribute(new OperandAttribute(operand)));
                }
                else if (token->GetTag() == TokenTag::To) {
                    PParseTreeNode parentIndexExp = node->Parent();
                    POperand beginLbl = GetBeginBlockLabel(parentIndexExp);

                    code.AddCommand(OpCode::LABEL, beginLbl, NULL, NULL);
                }
            }
        }
    }

    void CodeGenerator::BottomUpProcess(PParseTreeNode node, IntermediateCode& code) {
        PSymbol symbol = node->GetSymbol();
        assert(symbol.get() != NULL);

        if (symbol->GetType() == SymbolType::NonTerminal && !node->IsEmpty()) {
            PNonTerminal nonTerminal = boost::dynamic_pointer_cast<NonTerminal, Symbol>(symbol);
            assert(nonTerminal.get() != NULL);

            if (nonTerminal->GetTag() == NonTerminalTag::Factor) {
                MultipleTerminalTagPredicate terminalPred;
                terminalPred.AddTag(TokenTag::IntConstant);
                terminalPred.AddTag(TokenTag::RealConstant);
                terminalPred.AddTag(TokenTag::Identifier);

                PParseTreeNode terminalNode = node->FirstChild(terminalPred);

                if (terminalNode.get() != NULL) {
                    SetValue(node, GetValue(terminalNode));
                }
                else {
                    MultipleNonTerminalTagPredicate nonTermPred;
                    nonTermPred.AddTag(NonTerminalTag::Expression);
                    nonTermPred.AddTag(NonTerminalTag::FunctionCall);

                    PParseTreeNode nonTermNode = node->FirstChild(nonTermPred);
                    assert(nonTermNode.get() != NULL);

                    SetValue(node, GetValue(nonTermNode));
                }
            }
            else if (nonTerminal->GetTag() == NonTerminalTag::Term) {
                PParseTreeNode childTStroke = node->FirstChild(NonTerminalTagPredicate(NonTerminalTag::TermStroke));
                assert(childTStroke.get() != NULL);
                PParseTreeNode childF = node->FirstChild(NonTerminalTagPredicate(NonTerminalTag::Factor));
                assert(childF.get() != NULL);

                if (GetValue(childTStroke).get() != NULL) {
                    SetValue(node, GetValue(childTStroke));
                }
                else if (GetValue(childF).get() != NULL) {
                    SetValue(node, GetValue(childF));
                }
                else {
                    assert(false);
                }
            }
            else if (nonTerminal->GetTag() == NonTerminalTag::Expression) {
                //<E> => <T> <E1>
                PParseTreeNode childT = node->FirstChild(NonTerminalTagPredicate(NonTerminalTag::Term));
                assert(childT.get() != NULL);
                PParseTreeNode childEStroke = node->FirstChild(NonTerminalTagPredicate(NonTerminalTag::ExpressionStroke));
                assert(childEStroke.get() != NULL);

                if (GetValue(childEStroke).get() != NULL) {
                    SetValue(node, GetValue(childEStroke));
                }
                else if (GetValue(childT).get() != NULL) {
                    SetValue(node, GetValue(childT));
                }
                else {
                    assert(false);
                }
            }
            else if (
                nonTerminal->GetTag() == NonTerminalTag::ExpressionStroke ||
                nonTerminal->GetTag() == NonTerminalTag::TermStroke) {
                //<E'> => + <T> <E'>
                //<E'> => - <T> <E'>
                //<T'> => * <F> <T'>
                //<T'> => / <F> <T'>
                
                POperand result = GetTmpVariable();
                SetValue(node, result);

                POperand arg1;
                POperand arg2;

                PParseTreeNode parent = node->Parent();

                if (nonTerminal->GetTag() == NonTerminalTag::ExpressionStroke) {
                    //E' =>
                    arg1 = GetValue(parent->FirstChild(NonTerminalTagPredicate(NonTerminalTag::Term)));
                }
                else {
                    //T' =>
                    arg1 = GetValue(parent->FirstChild(NonTerminalTagPredicate(NonTerminalTag::Factor)));
                }

                arg2 = GetValue(node->Children()[2]);

                if (arg2.get() == NULL) {
                    arg2 = GetValue(node->Children()[1]);
                }

                OpCode::Enum opCode = GetArithmeticOpCode(node->Children()[0]);
                
                code.AddCommand(opCode, arg1, arg2, result);
            }
            else if (nonTerminal->GetTag() == NonTerminalTag::Assign) {
                //<assign> => id : = <E>

                POperand result = GetValue(node->FirstChild(TerminalTagPredicate(TokenTag::Identifier)));
                POperand exprValue = GetValue(node->FirstChild(NonTerminalTagPredicate(NonTerminalTag::Expression)));

                SetValue(node, result);

                code.AddCommand(OpCode::ASSIGN, exprValue, NULL, result);
            }
            else if (nonTerminal->GetTag() == NonTerminalTag::Param) {
                //<param> => <E>

                POperand paramValue = GetValue(node->FirstChild(NonTerminalTagPredicate(NonTerminalTag::Expression)));

                code.AddCommand(OpCode::PARAM, paramValue, NULL, NULL);
            }
            else if (nonTerminal->GetTag() == NonTerminalTag::Read) {
                POperand operand = GetValue(node->FirstChild(TerminalTagPredicate(TokenTag::Identifier)));

                code.AddCommand(OpCode::READ, NULL, NULL, operand);
            }
            else if (nonTerminal->GetTag() == NonTerminalTag::Write) {
                code.AddCommand(OpCode::WRITE, NULL, NULL, NULL);
            }
            else if (nonTerminal->GetTag() == NonTerminalTag::FunctionCall) {
                POperand result = GetTmpVariable();
                SetValue(node, result);

                PParseTreeNode stFuncNode = node->FirstChild(TerminalTagPredicate(TokenTag::StandardFunction));

                POperand funcName(new LabelOperand(GetFunctionName(stFuncNode)));

                code.AddCommand(OpCode::CALL, funcName, NULL, result);
            }
            else if (nonTerminal->GetTag() == NonTerminalTag::BooleanExpression) {
                PParseTreeNode parentIf = node->Parent();
                PParseTreeNode elseBlock = parentIf->FirstChild(NonTerminalTagPredicate(NonTerminalTag::Else));

                POperand falseLbl;

                if (!elseBlock->IsEmpty()) {
                    falseLbl = GetBeginBlockLabel(elseBlock);
                }
                else {
                    falseLbl = GetEndBlockLabel(parentIf);
                }

                //<bool-E> => <E> <bool-E'>

                PParseTreeNode boolStrokeNode = node->FirstChild(NonTerminalTagPredicate(NonTerminalTag::BooleanExpressionStroke));
                assert(boolStrokeNode.get() != NULL);
                PParseTreeNode boolOperatorNode = boolStrokeNode->Children()[0];

                OpCode::Enum opCode = GetInvertedBranchOpCode(boolOperatorNode);

                POperand arg1 = GetValue(node->Children()[0]);
                POperand arg2 = GetValue(boolStrokeNode->Children()[1]);

                code.AddCommand(opCode, arg1, arg2, falseLbl);
            }
            else if (nonTerminal->GetTag() == NonTerminalTag::IfThenElse) {
                POperand endIfLbl = GetEndBlockLabel(node);

                code.AddCommand(OpCode::LABEL, endIfLbl, NULL, NULL);
            }
            else if (nonTerminal->GetTag() == NonTerminalTag::For) {
                PParseTreeNode indexExpr = node->FirstChild(NonTerminalTagPredicate(NonTerminalTag::IndexExp));

                POperand indexId = GetValue(indexExpr->Children()[0]);
                POperand one(new IntOperand(1));

                code.AddCommand(OpCode::ADD, indexId, one, indexId);

                POperand indexExprBegin = GetBeginBlockLabel(indexExpr);

                code.AddCommand(OpCode::JMP, indexExprBegin, NULL, NULL);

                POperand endForLbl = GetEndBlockLabel(node);

                code.AddCommand(OpCode::LABEL, endForLbl, NULL, NULL);
            }
            else if (nonTerminal->GetTag() == NonTerminalTag::IndexExp) {
                //<index-exp> => <assign> to <E>
                PParseTreeNode parentFor = node->Parent();

                POperand indexResult = GetValue(node->Children()[0]);

                POperand condArg1 = GetValue(node->Children()[0]);
                POperand condArg2 = GetValue(node->Children()[2]);

                POperand forEndLbl = GetEndBlockLabel(parentFor);

                code.AddCommand(OpCode::BGT, condArg1, condArg2, forEndLbl);
            }
        }
    }

    OpCode::Enum CodeGenerator::GetArithmeticOpCode(PParseTreeNode node) const {
        PToken operationToken = node->GetToken();

        switch (operationToken->GetTag()) {
        case TokenTag::Plus:
            return OpCode::ADD;
        case TokenTag::Minus:
            return OpCode::SUB;
        case TokenTag::Slash:
            return OpCode::DIV;
        case TokenTag::Asterisk:
            return OpCode::MUL;
        default:
            //TODO: WTF IS THIS?!
            return OpCode::ADD;
        }
    }

    OpCode::Enum CodeGenerator::GetInvertedBranchOpCode(PParseTreeNode boolOperatorNode) const {
        PToken boolOperatorToken = boolOperatorNode->GetToken();
        assert(boolOperatorToken.get() != NULL);

        switch (boolOperatorToken->GetTag()) {
        case TokenTag::LessThan:
            return OpCode::BGE;
        case TokenTag::GreaterThan:
            return OpCode::BLE;
        case TokenTag::Equals:
            return OpCode::BNE;
        default:
            //TODO: OMG DON'T DO SUCH THINGS
            return OpCode::BNE;
        }
    }

    wstring CodeGenerator::GetFunctionName(PParseTreeNode node) const {
        PToken token = node->GetToken();
        assert(token.get() != NULL);
        assert(token->GetTag() == TokenTag::StandardFunction);

        StandardFunction* func = (StandardFunction*)token.get();

        return func->GetName();
    }

    PVariableOperand CodeGenerator::GetTmpVariable() {
        wstring varName = L"@tmp" + boost::lexical_cast<wstring, int>(++variablesCounter);

        return PVariableOperand(new VariableOperand(Variable(varName, true)));
    }

    PLabelOperand CodeGenerator::GetTmpLabel() {
        wstring labelName = L"@label" + boost::lexical_cast<wstring, int>(++labelsCounter);

        return PLabelOperand(new LabelOperand(labelName));
    }

    PLabelOperand CodeGenerator::GetBeginBlockLabel(PParseTreeNode node) const {
        return GetLabel("begin_block_lbl", node);
    }

    void CodeGenerator::SetBeginBlockLabel(PParseTreeNode node, PLabelOperand label) {
        SetLabel("begin_block_lbl", node, label);
    }

    PLabelOperand CodeGenerator::GetEndBlockLabel(PParseTreeNode node) const {
        return GetLabel("end_block_lbl", node);
    }

    void CodeGenerator::SetEndBlockLabel(PParseTreeNode node, PLabelOperand label) {
        SetLabel("end_block_lbl", node, label);
    }
    
    POperand CodeGenerator::GetValue(PParseTreeNode node) const {
        if (!node->HasAttribute("value")) {
            return POperand();
        }

        PSymbolAttribute attribute = node->GetAttribute("value");
        assert(attribute.get() != NULL);

        POperandAttribute operandAttribute = boost::dynamic_pointer_cast<OperandAttribute, SymbolAttribute>(attribute);
        assert(operandAttribute.get() != NULL);

        POperand operand = operandAttribute->GetOperand();

        return operand;
    }

    void CodeGenerator::SetValue(PParseTreeNode node, POperand value) {
        PSymbolAttribute attribute(new OperandAttribute(value));

        node->SetAttribute("value", attribute);
    }

    PLabelOperand CodeGenerator::GetLabel(const string& key, PParseTreeNode node) const {
        assert(node->HasAttribute(key));

        PSymbolAttribute attribute = node->GetAttribute(key);

        POperandAttribute operandAttribute = boost::dynamic_pointer_cast<OperandAttribute, SymbolAttribute>(attribute);

        assert(operandAttribute.get() != NULL);

        POperand operand = operandAttribute->GetOperand();

        assert(operand.get() != NULL);

        PLabelOperand labelOperand = boost::dynamic_pointer_cast<LabelOperand, Operand>(operand);

        assert(labelOperand.get() != NULL);

        return labelOperand;
    }

    void CodeGenerator::SetLabel(const string& key, PParseTreeNode node, PLabelOperand label) {
        PSymbolAttribute labelAttr = POperandAttribute(new OperandAttribute(label));

        node->SetAttribute(key, labelAttr);
    }
}
}