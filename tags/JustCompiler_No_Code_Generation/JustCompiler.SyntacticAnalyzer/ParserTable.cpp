#include "ParserTable.h"
#include <assert.h>

using namespace std;

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    ParserTable::ParserTable(const Grammar& grammar, FirstFunction& first, FollowFunction& follow) {
        vector<Production>::const_iterator prodIt;

        for (prodIt = grammar.Productions().cbegin(); prodIt != grammar.Productions().cend(); ++prodIt) {
            PNonTerminal left = prodIt->Left();
            TerminalSet& rightFirst = first(prodIt->Right());
            assert(first.IsCalculated(prodIt->Right()));
            TerminalSet::const_iterator firstIt;

            //for every terminal from first(right_part_of_production)
            for (firstIt = rightFirst.cbegin(); firstIt != rightFirst.cend(); ++firstIt) {
                //assert(tableInternal.find(ParserTableKey(left->GetTag(), firstIt->get()->GetTokenTag())) == tableInternal.cend());

                if (firstIt->get()->GetTokenTag() != SpecialTokenTag::Empty) {
                    AddEntry(left->GetTag(), firstIt->get()->GetTokenTag(), *prodIt);
                }
            }

            //follow(left_part_of_prod)
            TerminalSet& leftFollow = follow(left);
            assert(follow.IsCalculated(left));

            //if first(right_part_of_production) contains empty
            bool firstContainsEmpty = rightFirst.Contains(SpecialTokenTag::Empty);

            if (firstContainsEmpty) {
                TerminalSet::const_iterator followIt;

                for (followIt = leftFollow.cbegin(); followIt != leftFollow.cend(); ++followIt) {
                    //assert(tableInternal.find(ParserTableKey(left->GetTag(), followIt->get()->GetTokenTag())) == tableInternal.cend());
                    
                    AddEntry(left->GetTag(), followIt->get()->GetTokenTag(), *prodIt);
                }

                if (leftFollow.Contains(SpecialTokenTag::Eof)) {
                    //assert(tableInternal.find(ParserTableKey(left->GetTag(), SpecialTokenTag::Eof)) == tableInternal.cend());

                    AddEntry(left->GetTag(), SpecialTokenTag::Eof, *prodIt);
                }
            }
        }
    }

    vector<int> ParserTable::GetExpectedTerminals(int nonTerminalTag) const {
        vector<int> termtags;

        map<ParserTableKey, ParserTableEntry>::const_iterator it;

        for (it = tableInternal.cbegin(); it != tableInternal.cend(); ++it) {
            if (it->first.GetNonTerminalTag() == nonTerminalTag) {
                termtags.push_back(it->first.GetTerminalTag());
            }
        }

        return termtags;
    }

    void ParserTable::AddEntry(
        int nonTerminalTag,
        int terminalTag,
        const Production& production) {

        tableInternal[ParserTableKey(nonTerminalTag, terminalTag)] = ParserTableEntry(production);
    }

    void ParserTable::AddEntry(
        int nonTerminalTag,
        int terminalTag,
        int errorCode) {

        tableInternal[ParserTableKey(nonTerminalTag, terminalTag)] = ParserTableEntry(errorCode);
    }

    ParserTableEntry ParserTable::GetEntry(int nonTerminalTag, int terminalTag) const {
        map<ParserTableKey, ParserTableEntry>::const_iterator found = tableInternal.find(ParserTableKey(nonTerminalTag, terminalTag));

        if (found != tableInternal.end()) {
            return found->second;
        }
        else {
            //TODO: temporary solution
            return ParserTableEntry(-1);
        }
    }
}
}
}