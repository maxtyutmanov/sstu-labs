#include "WebApplicationSection.h"

using namespace std;

namespace JustServer {
namespace Configuration {

    WebApplicationSection::WebApplicationSection(const wstring& physicalPath, unsigned short port) 
        : physicalPath(physicalPath), port(port){
    }

    wstring WebApplicationSection::GetPhysicalPath() const {
        return physicalPath;
    }

    unsigned short WebApplicationSection::GetPort() const {
        return port;
    }

}
}