#pragma once

namespace JustCompiler {
namespace LexicalAnalyzer {

    struct TokenTag {
        enum Enum {
            //keywords

            Program,
            Var,
            For,
            Begin,
            End,
            Type_Int,
            Type_Real,
            Read,
            Write,
            Do,
            To,
            If,
            Then,
            Else,
            Goto,

            //One character tokens
            Plus,
            Minus,
            Asterisk,
            Colon,
            Underscore,
            Slash,
            OpeningRoundBracket,
            ClosingRoundBracket,
            OpeningBrace,
            ClosingBrace,
            Equals,
            LessThan,
            GreaterThan,
            OpeningSquareBracket,
            ClosingSquareBracket,
            Semicolon,
            Quotes,
            SingleQuotes,
            Comma,

            //Other tokens

            Identifier,
            IntConstant,
            RealConstant,
            StringLiteral,
            StandardFunction,
            Unrecognized = -1
        };
    };

}
}