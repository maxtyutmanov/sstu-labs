#include "Production.h"
#include "Terminal.h"
#include <SpecialTokenTag.h>

using namespace std;
using JustCompiler::LexicalAnalyzer::SpecialTokenTag;

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    Production::Production(PNonTerminal left, const SymbolString& right) 
        : left(left), right(right) { }

    PNonTerminal Production::Left() const {
        return left;
    }

    SymbolString Production::Right() const {
        return right;
    }

    bool Production::ToEmpty() const {
        if (right.size() == 0) {
            //there must be empty symbol (explicitly)
            return false;
        }

        bool result = true;

        vector<PSymbol>::const_iterator it;

        for (it = right.cbegin(); it != right.cend(); ++it) {
            if (it->get()->GetType() == SymbolType::Terminal) {
                PTerminal asTerminal = boost::dynamic_pointer_cast<Terminal, Symbol>(*it);
                
                if (asTerminal->GetTokenTag() != SpecialTokenTag::Empty) {
                    result = false;
                    break;
                }
            }
            else {
                result = false;
                break;
            }
        }

        return result;
    }
}
}
}