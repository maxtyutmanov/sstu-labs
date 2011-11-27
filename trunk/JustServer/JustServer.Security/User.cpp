#include "User.h"

using namespace std;

namespace JustServer {
namespace Http {
namespace Security {

    User::User(const string& name, const vector<string>& roles)
        : name(name), roles(roles) {}

    string User::GetName() const {
        return name;
    }

    bool User::IsInRole(const string& role) const {
        vector<string>::const_iterator rolesIt;
        
        for (rolesIt = roles.begin(); rolesIt != roles.end(); ++rolesIt) {
            if (*rolesIt == role) {
                return true;
            }
        }

        return false;
    }

}
}
}