#ifndef TOKEN_TAG_H
#define TOKEN_TAG_H

namespace JustServer {
namespace HttpGrammar {

    struct TokenTag {
        enum Enum {
            HttpVerb = 1,
            Uri = 2,
            HttpVersion = 3,
            Header = 4,
            Body = 5
        };
    };

}
}

#endif