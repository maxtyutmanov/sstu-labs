#pragma once

namespace JustCompiler {
namespace ParserGrammar {

    struct NonTerminalTag {
        enum Enum {
            Prog,
            DecList,
            DecListStroke,
            StmtList,
            StmtListStroke,
            Dec,
            IdList,
            Type,
            IdListStroke,
            Stmt,
            Assign,
            Read,
            Write,
            For,
            IndexExp,
            Body,
            IfThenElse,
            IfThen,
            Else,
            Expression,
            ExpressionStroke,
            Term,
            TermStroke,
            Factor,
            BooleanExpression,
            BooleanExpressionStroke,
            ParamList,
            ParamListStroke,
            Param,
            Goto,
            FunctionCall
        };
    };

}
}