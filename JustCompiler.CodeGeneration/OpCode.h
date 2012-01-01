#pragma once

namespace JustCompiler {
namespace CodeGeneration {

    struct OpCode {
        enum Enum {
            Add,
            Mul,
            Div,
            Sub,
            ASSIGN,
            JMP
        };
    };

}
}