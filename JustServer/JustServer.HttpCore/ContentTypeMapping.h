#ifndef CONTENT_TYPE_MAPPING
#define CONTENT_TYPE_MAPPING

#include <string>
#include <map>
#include <boost/filesystem.hpp>
#include "HttpRequest.h"

namespace JustServer {
namespace Http {

    class ContentTypeMapping {
    public:
        ContentTypeMapping();

        std::string GetContentType(const HttpRequest& request, boost::filesystem3::path& resourcePath) const;
    private:
        //mapping from file extensions to mime types and subtypes
        std::map<std::string, std::string> mimeTypes;
        std::map<std::string, std::string> mimeSubtypes;
    };

}
}

#endif