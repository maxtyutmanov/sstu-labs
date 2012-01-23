#pragma once

namespace JustCompiler {
namespace CodeGeneration {

    struct OpCode {
        enum Enum {
            ADD,
            MUL,
            DIV,
            SUB,
            ASSIGN,
            JMP,
            LABEL,
            PARAM,
            READ,
            WRITE,
            CALL,
            BGE,
            BLE,
            BNE,
            BGT
        };
    };

}
}