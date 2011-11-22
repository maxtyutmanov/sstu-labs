#ifndef I_FILE_SYSTEM_SERVICE
#define I_FILE_SYSTEM_SERVICE

#include <iostream>
#include <string>

namespace JustServer {
namespace FileSystemAccess {

    //Provides readonly access to server's file system
    class IFileSystemService {
    public:
        virtual std::istream& GetFileStream(std::string siteRoot, std::string absolutePath) const = 0;
        virtual bool FileExists(std::string siteRoot, std::string absolutePath) const = 0;
    };

}
}

#endif