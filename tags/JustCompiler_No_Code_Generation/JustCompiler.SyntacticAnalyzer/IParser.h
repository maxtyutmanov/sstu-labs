#pragma once

#include "ParseTree.h"
#include "SyntaxError.h"
#include <ITokenStream.h>
#include <memory>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SyntacticAnalyzer {

    struct ParserOutput {
        ParserOutput(PParseTreeNode parseTreeRoot)
            : parseTree(ParseTree(parseTreeRoot)) {}

        ParseTree parseTree;
        std::vector<PSyntaxError> errors;

        virtual ~ParserOutput() {};
    };

    class IParser {
    public:
        virtual std::auto_ptr<ParserOutput> Parse(boost::shared_ptr<JustCompiler::LexicalAnalyzer::ITokenStream> tokenStream) = 0;
        virtual ~IParser() {};
    };

}
}