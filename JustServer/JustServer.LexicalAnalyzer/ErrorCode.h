#pragma once

struct ErrorCode {
    enum Enum {
        TooLongIdentifier = 1,
        UnknownLexeme = 2,
        TooLargeIntConstant = 3,
        IdStartingWithDigit = 4,
        IdWithWrongCharset = 5,
        UnterminatedStringLiteral = 6,
        UnterminatedComment = 7,
        IntConstantStartingWithZero = 8
    };
};