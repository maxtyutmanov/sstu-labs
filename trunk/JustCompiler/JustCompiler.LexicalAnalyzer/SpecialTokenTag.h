#pragma once

namespace JustCompiler {
namespace LexicalAnalyzer {

    struct SpecialTokenTag {
        enum Enum {
            Unrecognized = -1,
            Eof = -2,
            Empty = -3
        };
    };

}
}