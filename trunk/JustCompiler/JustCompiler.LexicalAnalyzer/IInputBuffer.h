#pragma once

#include "Global.h"

namespace JustCompiler {
namespace LexicalAnalyzer {

    class IInputBuffer {
    public:
        virtual char_type Get() = 0;
        virtual void Unget() = 0;
        virtual bool Eof() const = 0;
        virtual int GetLineNumber() const = 0;
        virtual int GetCharacterNumber() const = 0;

        virtual ~IInputBuffer() {};
    };

}
}