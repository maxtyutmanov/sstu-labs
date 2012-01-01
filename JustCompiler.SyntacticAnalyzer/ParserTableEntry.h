#pragma once

#include "Production.h"
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    class ParserTableEntry {
    public:
        ParserTableEntry() {}
        
        ParserTableEntry(int errorCode) {
            assert(errorCode != 0);
            this->errorCode = errorCode;
        }

        ParserTableEntry(const Production& production) {
            this->errorCode = 0;
            this->pProduction.reset(new Production(production));
        }

        /*ParserTableEntry(const ParserTableEntry& right) {
            this->pProduction = right.pProduction;
            this->errorCode = right.errorCode;
        }*/

        bool IsError() const {
            return ErrorCode() != 0;
        }

        int ErrorCode() const {
            return errorCode;
        }

        const Production* GetProduction() const {
            return pProduction.get();
        }

    private:
        boost::shared_ptr<Production> pProduction;
        int errorCode;
    };

}
}
}