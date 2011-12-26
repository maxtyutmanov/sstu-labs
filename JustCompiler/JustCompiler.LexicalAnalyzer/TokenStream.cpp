#include "TokenStream.h"

using namespace std;

namespace JustCompiler {
namespace LexicalAnalyzer {

    TokenStream::TokenStream(const vector<PToken>& tokens) 
        :tokens(tokens) { 

        currentIndex = 0;
    }

    PToken TokenStream::Peak() const {
        return tokens.at(currentIndex);
    }

    void TokenStream::MoveForward() {
        ++currentIndex;
    }

    bool TokenStream::EndOfStream() const {
        return currentIndex >= tokens.size();
    }

    int TokenStream::LineNum() const {
        if (currentIndex < tokens.size() - 1) {
            return tokens.at(currentIndex)->GetLineNum();
        }
        else {
            return tokens[tokens.size() - 1]->GetLineNum();
        }
    }

    int TokenStream::CharNum() const {
        if (currentIndex < tokens.size() - 1) {
            return tokens.at(currentIndex)->GetCharNum();
        }
        else {
            return 1;
        }
    }
}
}