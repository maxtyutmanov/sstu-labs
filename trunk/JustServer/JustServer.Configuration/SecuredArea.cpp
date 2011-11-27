#include "SecuredArea.h"

using namespace std;

namespace JustServer {
namespace Configuration {

    SecuredArea::SecuredArea(const string& name, const string& path, const vector<string>& roles) 
        : name(name), path(path), roles(roles) { }

    string SecuredArea::GetName() const {
        return name;
    }

    string SecuredArea::GetPath() const {
        return path;
    }

    const vector<string>& SecuredArea::GetRoles() const {
        return roles;
    }
}
}