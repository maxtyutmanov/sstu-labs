#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include "IUserRepository.h"

namespace JustServer {
namespace Http {
namespace Security {

    class UserRepository : public IUserRepository {
    public:
        UserRepository(const std::wstring& databasePath);

        virtual std::auto_ptr<User> GetUser(const std::string& name, const std::string& password) const;
    private:
        std::wstring databasePath;
    };

}
}
}

#endif