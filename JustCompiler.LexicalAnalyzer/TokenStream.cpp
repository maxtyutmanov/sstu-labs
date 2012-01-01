#include "TokenStream.h"
#include "SpecialTokenTag.h"

using namespace std;

namespace JustCompiler {
namespace LexicalAnalyzer {

    TokenStream::TokenStream(const vector<PToken>& tokens) 
        :tokens(tokens) { 

        if (tokens.size() == 0) {
            this->tokens.push_back(PToken(new Token(SpecialTokenTag::Eof)));
        }
        else if (tokens[tokens.size() - 1]->GetTag() != SpecialTokenTag::Eof) {
            this->tokens.push_back(PToken(new Token(SpecialTokenTag::Eof,tokens[tokens.size() - 1]->GetLineNum() + 1, 1)));
        }

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