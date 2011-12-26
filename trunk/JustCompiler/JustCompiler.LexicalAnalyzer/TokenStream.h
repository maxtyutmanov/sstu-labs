#pragma once

#include "ITokenStream.h"
#include <vector>

namespace JustCompiler {
namespace LexicalAnalyzer {

    class TokenStream : public ITokenStream {
    public:
        TokenStream(const std::vector<PToken>& tokens);

        virtual PToken Peak() const;
        virtual void MoveForward();
        virtual bool EndOfStream() const;
        virtual int LineNum() const;
        virtual int CharNum() const;
    private:
        std::vector<PToken> tokens;
        int currentIndex;
    };

}
}