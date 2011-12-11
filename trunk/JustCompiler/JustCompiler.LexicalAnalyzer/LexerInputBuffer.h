#pragma once

#include "Global.h"
#include "IInputBuffer.h"
#include <map>
using std::map;

namespace JustCompiler {
namespace LexicalAnalyzer {

    class LexerInputBuffer : public IInputBuffer {
    public:
        explicit LexerInputBuffer(input_stream_type &input);

        virtual char_type Get();
        virtual void Unget();
        virtual bool Eof() const;
        virtual int GetLineNumber() const;
        virtual int GetCharacterNumber() const;
    private:
        string_type input;
        int cursor;
        int lineNumber;
        int characterNumber;
        //correspondence between line numbers and character counts in this lines
        map<int, int> characterCounts;

        void GoToNewLine();
        void GoToPreviousLine();
    };

}
}