#pragma once

#include "Command.h"
#include "Variable.h"
#include <ParseTree.h>
#include <SymbolTable.h>
#include "IntermediateCode.h"
#include <vector>

namespace JustCompiler {
namespace CodeGeneration {

    class CodeGenerator {
    public:
        CodeGenerator();

        IntermediateCode GenerateCode(SyntacticAnalyzer::ParseTree& parseTree);
    private:
        int variablesCounter;
        int labelsCounter;

        void TopDownProcess(SyntacticAnalyzer::PParseTreeNode node, IntermediateCode& code);
        void BottomUpProcess(SyntacticAnalyzer::PParseTreeNode node, IntermediateCode& code);

        PVariableOperand GetTmpVariable();
        PLabelOperand GetTmpLabel();

        PLabelOperand GetBeginBlockLabel(const SyntacticAnalyzer::PParseTreeNode node) const;
        void SetBeginBlockLabel(SyntacticAnalyzer::PParseTreeNode node, PLabelOperand label);
        PLabelOperand GetEndBlockLabel(const SyntacticAnalyzer::PParseTreeNode node) const;
        void SetEndBlockLabel(SyntacticAnalyzer::PParseTreeNode node, PLabelOperand label);
        POperand GetValue(const SyntacticAnalyzer::PParseTreeNode node) const;
        void SetValue(SyntacticAnalyzer::PParseTreeNode node, POperand value);

        PLabelOperand GetLabel(const std::string& key, const SyntacticAnalyzer::PParseTreeNode node) const;
        void SetLabel(const std::string& key, SyntacticAnalyzer::PParseTreeNode node, PLabelOperand label);

        OpCode::Enum GetArithmeticOpCode(SyntacticAnalyzer::PParseTreeNode node) const;
        std::wstring GetFunctionName(SyntacticAnalyzer::PParseTreeNode node) const;
        OpCode::Enum GetInvertedBranchOpCode(SyntacticAnalyzer::PParseTreeNode boolOperatorNode) const;
    };

}
}