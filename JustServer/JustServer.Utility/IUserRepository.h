#ifndef I_USER_REPOSITORY_H
#define I_USER_REPOSITORY_H

#include <string>
#include <vector>
#include <memory>
#include "User.h"

namespace JustServer {
namespace Http {
namespace Security {

    class IUserRepository {
    public:
        virtual std::auto_ptr<User> GetUser(const std::string& name, const std::string& password) const = 0;
    };

}
}
}

#endif