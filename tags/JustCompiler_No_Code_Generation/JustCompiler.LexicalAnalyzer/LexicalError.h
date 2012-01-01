#pragma once

#include <string>
#include <boost/shared_ptr.hpp>
using std::wstring;

namespace JustCompiler {
namespace LexicalAnalyzer {

    class LexicalError;
    typedef boost::shared_ptr<LexicalError> PLexicalError;

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