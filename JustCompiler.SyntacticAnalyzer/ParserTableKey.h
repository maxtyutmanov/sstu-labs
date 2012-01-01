#pragma once

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    class ParserTableKey {
    public:
        ParserTableKey(int nonTerminalTag, int terminalTag)
            : nonTerminalTag(nonTerminalTag), terminalTag(terminalTag) {}

        int GetNonTerminalTag() const {
            return nonTerminalTag;
        }

        int GetTerminalTag() const {
            return terminalTag;
        }

        bool operator <(const ParserTableKey& right) const {
            if (this->nonTerminalTag != right.nonTerminalTag) {
                return this->nonTerminalTag < right.nonTerminalTag;
            }
            else {
                return this->terminalTag < right.terminalTag;
            }
        }

        bool operator ==(const ParserTableKey& right) const {
            return this->nonTerminalTag == right.nonTerminalTag && this->terminalTag == right.terminalTag;
        }
    private:
        int nonTerminalTag;
        int terminalTag;
    };

}
}
}