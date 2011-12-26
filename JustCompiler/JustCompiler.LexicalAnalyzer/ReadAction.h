#pragma once

namespace JustCompiler {
namespace LexicalAnalyzer {

    struct ReadAction {

        //format: InputBufferAction_CurrentLexemeBufferAction
        enum Enum {
            RemoveFromBuffer_Ignore,
            RemoveFromBuffer_AddToLexeme,
            KeepInBuffer_Ignore,
            KeepInBuffer_ClearLexeme,
            RemoveFromBuffer_ClearLexeme    //HACK: this is hack, I have to admit :-(
        };
    };
}
}