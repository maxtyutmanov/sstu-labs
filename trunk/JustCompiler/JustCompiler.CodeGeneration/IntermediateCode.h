#pragma once

#include <vector>
#include "Operand.h"
#include "OpCode.h"
#include "Command.h"

namespace JustCompiler {
namespace CodeGeneration {

    class IntermediateCode {
    public:
        void AddCommand(OpCode::Enum opCode, POperand& firstOp, void* plc2, void* plcRes) {
            assert(plc2 == NULL);
            assert(plcRes == NULL);
            AddCommand(opCode, firstOp, POperand(), POperand());
        }

        void AddCommand(OpCode::Enum opCode, POperand& firstOp, POperand& secondOp, void* plcRes) {
            assert(plcRes == NULL);
            AddCommand(opCode, firstOp, secondOp, POperand());
        }

        void AddCommand(OpCode::Enum opCode, POperand& firstOp, POperand& secondOp, POperand& result) {
            commands.push_back(Command(opCode, firstOp, secondOp, result));
        }

        void AddCommand(OpCode::Enum opCode, void* plc1, void* plc2, void* plcRes) {
            assert(plc1 == NULL);
            assert(plc2 == NULL);
            assert(plcRes == NULL);
            AddCommand(opCode, POperand(), POperand(), POperand());
        }

        void AddCommand(OpCode::Enum opCode, void* plc1, void* plc2, POperand result) {
            assert(plc1 == NULL);
            assert(plc2 == NULL);
            AddCommand(opCode, POperand(), POperand(), result);
        }

        void AddCommand(OpCode::Enum opCode, POperand& firstOp, void* plc2, POperand result) {
            assert(plc2 == NULL);

            AddCommand(opCode, firstOp, POperand(), result);
        }

        std::vector<Command> GetCommands() const {
            return commands;
        }
    private:
        std::vector<Command> commands;
    };

}
}