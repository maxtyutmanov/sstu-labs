#pragma once

#include <Identifier.h>
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SemanticAnalyzer {

    class SymbolTable;
    typedef boost::shared_ptr<SymbolTable> PSymbolTable;

    class SymbolTable {
    public:
        void AddEntry(LexicalAnalyzer::Tokens::PIdentifier id);
        bool HasEntry(const std::string& name) const;
        LexicalAnalyzer::Tokens::PIdentifier GetEntry(const std::string& name) const;
    private:
        std::map<std::string, LexicalAnalyzer::Tokens::PIdentifier> tableInternal;
    };

}
}