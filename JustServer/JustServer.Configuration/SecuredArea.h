#ifndef SECURED_SECTION_H
#define SECURED_SECTION_H

#include <string>
#include <vector>

namespace JustServer {
namespace Configuration {

    class SecuredArea {
    public:
        SecuredArea(const std::string& name, const std::string& path, const std::vector<std::string>& roles);

        std::string GetName() const;
        std::string GetPath() const;
        const std::vector<std::string>& GetRoles() const;
    private:
        std::string name;
        std::string path;
        std::vector<std::string> roles;
    };

}
}

#endif