#pragma once

#include <string>
#include <assert.h>
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SyntacticAnalyzer {

    class SymbolAttribute;
    typedef boost::shared_ptr<SymbolAttribute> PSymbolAttribute;

    class SymbolAttribute {
    public:
        virtual int GetAttributeType() const = 0;
    };

}
}