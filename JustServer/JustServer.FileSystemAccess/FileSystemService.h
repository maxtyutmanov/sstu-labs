#ifndef FILE_SYSTEM_SERVICE
#define FILE_SYSTEM_SERVICE

#include "IFileSystemService.h"

namespace JustServer {
namespace FileSystemAccess {

    class FileSystemService : public IFileSystemService {
    public:
        virtual std::istream& GetFileStream(std::string siteRoot, std::string absolutePath) const;
        virtual bool FileExists(std::string siteRoot, std::string absolutePath) const;
    };

}
}

#endif