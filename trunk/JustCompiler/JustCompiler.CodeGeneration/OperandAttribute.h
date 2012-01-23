#pragma once

#include <SymbolAttribute.h>
#include "AttributeType.h"
#include "Operand.h"

namespace JustCompiler {
namespace CodeGeneration {

    class OperandAttribute;
    typedef boost::shared_ptr<OperandAttribute> POperandAttribute;

    class OperandAttribute : public SyntacticAnalyzer::SymbolAttribute {
    public:
        OperandAttribute(POperand operand)
            : operand(operand) {}

        POperand GetOperand() const {
            return operand;
        }

        virtual int GetAttributeType() const {
            return AttributeType::Operand;
        }
    private:
        POperand operand;
    };

}
}