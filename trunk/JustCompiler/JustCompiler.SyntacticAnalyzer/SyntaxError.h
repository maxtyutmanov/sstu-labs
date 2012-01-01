#pragma once

#include "ErrorClass.h"
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SyntacticAnalyzer {

    class SyntaxError {
    public:
        SyntaxError(int lineNum, int charNum, ErrorClass::Enum errorClass);
        virtual ErrorClass::Enum GetErrorClass() const;

        int GetLineNum() const;
        int GetCharNum() const;
    private:
        ErrorClass::Enum errorClass;
        int lineNum;
        int charNum;
    };

    typedef boost::shared_ptr<SyntaxError> PSyntaxError;
}
}