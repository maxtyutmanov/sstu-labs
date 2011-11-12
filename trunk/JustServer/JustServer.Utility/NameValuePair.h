#ifndef NAME_VALUE_PAIR_H
#define NAME_VALUE_PAIR_H

#include <string>
using std::string;

namespace JustServer {
namespace Utility {

    struct NameValuePair {
        NameValuePair(const string& name, const string& value) 
            : name(name), value(value) { }

        string name;
        string value;
    };

}
}

#endif