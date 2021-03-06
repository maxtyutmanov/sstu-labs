#pragma once

#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace LexicalAnalyzer {

    class Token;
    typedef boost::shared_ptr<Token> PToken;

    class Token {
    public:
        Token(const int tag, const int lineNum, const int charNum);
        Token(const int tag);

        virtual ~Token();

        int GetTag() const;
        int GetLineNum() const;
        void SetLineNum(const int lineNum);
        int GetCharNum() const;
        void SetCharNum(const int charNum);

        virtual bool operator== (const Token& right) const;
    protected:
        int tag;
        int lineNum;
        int charNum;
    };

}
}