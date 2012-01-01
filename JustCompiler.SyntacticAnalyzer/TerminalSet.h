#pragma once

#include "Terminal.h"
#include <SpecialTokenTag.h>
#include <boost/shared_ptr.hpp>
#include <vector>

using namespace JustCompiler::LexicalAnalyzer;

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    class TerminalSet : public std::vector<PTerminal> {
    public:
        TerminalSet() {}

        TerminalSet(PTerminal terminal) {
            this->push_back(terminal);
        }

        virtual ~TerminalSet() {}

        //true if one or more symbols were actually added to the set
        bool Merge(TerminalSet terminals, bool addEmpty) {
            bool added = false;

            for (size_t i = 0; i < terminals.size(); ++i) {
                if (!addEmpty && terminals[i]->GetTokenTag() == SpecialTokenTag::Empty) {
                    continue;
                }

                if (!this->Contains(terminals[i]->GetTokenTag())) {
                    this->push_back(terminals[i]);
                    added = true;
                }
            }

            return added;
        }

        bool Contains(int tag) {
            std::vector<PTerminal>::const_iterator it;

            for (it = this->cbegin(); it != this->cend(); ++it) {
                if (it->get()->GetTokenTag() == tag) {
                    return true;
                }
            }

            return false;
        }
    };

}
}
}