#include "ContentTypeMapping.h"

using namespace std;

namespace JustServer {
namespace Http {

    ContentTypeMapping::ContentTypeMapping() {
        mimeTypes[".jpg"] = "image";
        mimeTypes[".jpeg"] = "image";
        mimeTypes[".png"] = "image";
        mimeTypes[".gif"] = "image";
        mimeTypes[".pdf"] = "application";
        mimeTypes[".swf"] = "application";
        mimeTypes[".js"] = "text";
        mimeTypes[".htm"] = "text";
        mimeTypes[".html"] = "text";
        mimeTypes[".css"] = "text";
        mimeTypes[".xml"] = "text";

        mimeSubtypes[".jpg"] = "jpeg";
        mimeSubtypes[".jpeg"] = "jpeg";
        mimeSubtypes[".png"] = "png";
        mimeSubtypes[".gif"] = "gif";
        mimeSubtypes[".pdf"] = "pdf";
        mimeSubtypes[".swf"] = "x-shockwave-flash";
        mimeSubtypes[".js"] = "javascript";
        mimeSubtypes[".htm"] = "html";
        mimeSubtypes[".html"] = "html";
        mimeSubtypes[".css"] = "css";
        mimeSubtypes[".xml"] = "xml";
    }

    string ContentTypeMapping::GetContentType(const HttpRequest& request, boost::filesystem3::path& resourcePath) const {
        string fileExtension = boost::filesystem3::extension(resourcePath);

        map<string, string>::const_iterator typeIt = mimeTypes.find(fileExtension);
        map<string, string>::const_iterator subtypeIt = mimeSubtypes.find(fileExtension);

        string contentType;

        if (typeIt != mimeTypes.end() && subtypeIt != mimeSubtypes.end()) {
            contentType = typeIt->second + "/" + subtypeIt->second;

            if (typeIt->second == "text") {
                contentType += "; charset=utf-8";
            }
        }
        else {
            //TODO: it's not the right thing to do
            contentType = "text/plain";
        }

        return contentType;
    }
}
}