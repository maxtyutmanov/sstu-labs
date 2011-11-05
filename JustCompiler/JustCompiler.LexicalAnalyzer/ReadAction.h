#pragma once

struct ReadAction {

    //format: InputBufferAction_CurrentLexemeBufferAction
    enum Enum {
        RemoveFromBuffer_Ignore,
        RemoveFromBuffer_AddToLexeme,
        KeepInBuffer_Ignore,
        RemoveFromBuffer_ClearLexeme    //HACK: this is hack, I have to admit :-(
    };
};