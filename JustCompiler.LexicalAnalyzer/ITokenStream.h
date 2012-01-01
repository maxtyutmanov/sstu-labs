#pragma once

#include "Token.h"
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace LexicalAnalyzer {

    class ITokenStream {
    public:
        virtual boost::shared_ptr<Token> Peak() const = 0;
        virtual void MoveForward() = 0;
        virtual bool EndOfStream() const = 0;
        virtual int LineNum() const = 0;
        virtual int CharNum() const = 0;
    };

}
}