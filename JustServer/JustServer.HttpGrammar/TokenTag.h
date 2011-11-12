#ifndef TOKEN_TAG_H
#define TOKEN_TAG_H

namespace JustServer {
namespace HttpGrammar {

    struct TokenTag {
        enum Enum {
            HttpVerb = 1,
            Uri = 2,
            HttpVersion = 3,
            HeaderName = 4,
            HeaderValue = 5,
            Body
        };
    };

}
}

#endif