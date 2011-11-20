#ifndef REASON_PHRASE_MAPPING_H
#define REASON_PHRASE_MAPPING_H

#include <string>
#include <map>

namespace JustServer {
namespace Http {

    class ReasonPhraseMapping {
    public:
        ReasonPhraseMapping();

        std::string GetReasonPhrase(int code) const;
    private:
        std::map<int, std::string> mapping;
    };

}
}

#endif