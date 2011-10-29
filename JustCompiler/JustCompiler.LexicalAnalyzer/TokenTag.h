#pragma once

struct TokenTag {
    enum Enum {
        //keywords

        Program,
        While,
        For,
        Array,
        Begin,
        End,
        Type_Int,
        Type_Float,
        Type_String,

        //standard functions

        Sqrt,
        Log,
        Ln,
        Nearby,

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
        Space,
        IntConstant,
        StringLiteral,
        Newline,
        Unrecognized
    };
};