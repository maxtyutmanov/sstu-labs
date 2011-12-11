#pragma once

#include <string>
using std::wstring;

namespace JustCompiler {
namespace LexicalAnalyzer {

    class LexicalError {
    public:
        LexicalError();
        LexicalError(const int lineNumber, const int charNumber, const int errorCode);

        int GetLineNumber() const;
        int GetCharNumber() const;
        int GetErrorCode() const;
    private:
        int lineNumber;
        int charNumber;
        int errorCode;
    };

}
}