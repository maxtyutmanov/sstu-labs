#ifndef I_USER_H
#define I_USER_H

#include <string>

namespace JustServer {
namespace Http {
namespace Security {

    class IUser {
    public:
        virtual std::string GetName() const = 0;
    };

}
}
}

#endif