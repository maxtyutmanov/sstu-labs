#ifndef WEB_APPLICATION_SECTION_H
#define WEB_APPLICATION_SECTION_H

#include <string>

namespace JustServer {
namespace Configuration {

    class WebApplicationSection {
    public:
        WebApplicationSection(const std::wstring& physicalPath, unsigned short port);

        std::wstring GetPhysicalPath() const;
        unsigned short GetPort() const;
    private:
        std::wstring physicalPath;
        unsigned short port;
    };

}
}

#endif