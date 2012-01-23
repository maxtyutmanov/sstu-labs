#pragma once

#include "OpCode.h"
#include "Operand.h"

namespace JustCompiler {
namespace CodeGeneration {

    class Command {
    public:
        Command(const OpCode::Enum opCode, POperand firstOperand, POperand secondOperand, POperand result);
        std::wstring ToString() const;
    private:
        OpCode::Enum opCode;
        POperand firstOperand;
        POperand secondOperand;
        POperand result;
    };

}
}