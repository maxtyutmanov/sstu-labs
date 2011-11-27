#ifndef USER_H
#define USER_H

#include <IUser.h>
#include <string>
#include <vector>

namespace JustServer {
namespace Http {
namespace Security {

    class User : public IUser {
    public:
        User(const std::string& name, const std::vector<std::string>& roles);

        virtual std::string GetName() const;
        bool IsInRole(const std::string& role) const;
    private:
        std::string name;
        std::vector<std::string> roles;
    };

}
}
}

#endif