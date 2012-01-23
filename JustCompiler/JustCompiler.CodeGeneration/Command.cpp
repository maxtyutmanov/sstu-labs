#include "Command.h"

using namespace std;

namespace JustCompiler {
namespace CodeGeneration {

    Command::Command(const OpCode::Enum opCode, POperand firstOperand, POperand secondOperand, POperand result)
        : opCode(opCode), firstOperand(firstOperand), secondOperand(secondOperand), result(result) {}

    wstring Command::ToString() const {
        wstring opCodeStr;

        switch (opCode) {
        case OpCode::ADD:
            opCodeStr = L"ADD";
            break;
        case OpCode::ASSIGN:
            opCodeStr = L"ASSIGN";
            break;
        case OpCode::DIV:
            opCodeStr = L"DIV";
            break;
        case OpCode::JMP:
            opCodeStr = L"JUMP";
            break;
        case OpCode::LABEL:
            opCodeStr = L"LABEL";
            break;
        case OpCode::MUL:
            opCodeStr = L"MUL";
            break;
        case OpCode::SUB:
            opCodeStr = L"SUB";
            break;
        case OpCode::PARAM:
            opCodeStr = L"PUSH_PARAM";
            break;
        case OpCode::READ:
            opCodeStr = L"READ";
            break;
        case OpCode::WRITE:
            opCodeStr = L"WRITE";
            break;
        case OpCode::CALL:
            opCodeStr = L"CALL";
            break;
        case OpCode::BGE:
            opCodeStr = L"BGE";
            break;
        case OpCode::BLE:
            opCodeStr = L"BLE";
            break;
        case OpCode::BNE:
            opCodeStr = L"BNE";
            break;
        case OpCode::BGT:
            opCodeStr = L"BGT";
            break;
        }

        wstring firstOperandStr = (firstOperand.get() != NULL ? firstOperand->ToString() : L"");
        wstring secondOperandStr = (secondOperand.get() != NULL ? secondOperand->ToString() : L"");
        wstring resultStr = (result.get() != NULL ? result->ToString() : L"");

        return opCodeStr + L"\t\t" + firstOperandStr + L"\t\t" + secondOperandStr + L"\t\t" + resultStr;
    }
}
}