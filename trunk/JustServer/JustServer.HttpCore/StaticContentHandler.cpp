#include "StaticContentHandler.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <string>
#include <fstream>
#include <algorithm>
#include <boost/algorithm/string/classification.hpp>

using namespace std;

namespace JustServer {
namespace Http {
namespace StandardHandlers {

    ContentTypeMapping StaticContentHandler::contentTypeMapping;

    bool StaticContentHandler::CanHandleRequest(const HttpRequest& request) const {
        //TODO: include some logic here if needed
        return true;
    }

    auto_ptr<HttpResponse> StaticContentHandler::HandleRequest(const HttpRequest& request) const {
        auto_ptr<HttpResponse> response(new HttpResponse(request.GetHttpVersion()));

        wstring wpathStr = request.GetPhysicalPath();

        boost::filesystem3::path resourcePath(wpathStr);

        if (!boost::filesystem3::exists(resourcePath)) {
            response->AppendToResponseBody("<html><head><title>Not Found</title></head><body><h1>404 Not Found</h1></body></html>");
            response->SetStatusCode(404);
            response->SetHeader("content-type", "text/html");
        }
        else {
            replace_if(wpathStr.begin(), wpathStr.end(), boost::is_any_of(L"/"), L'\\');

            ifstream fileInput(wpathStr, std::ios_base::binary);

            if (fileInput.good()) {
                string fileContents;
                //determining length of the file (for optimization purposes)
                fileInput.seekg(0, std::ios::end);
                fileContents.reserve(fileInput.tellg());
                fileInput.seekg(0, std::ios::beg);

                //TODO: this works way too slow :-(
                fileContents.assign(istreambuf_iterator<char>(fileInput), istreambuf_iterator<char>());
                response->AppendToResponseBody(fileContents);
                response->SetHeader("content-type", contentTypeMapping.GetContentType(request, resourcePath));
            }
            else {
                response->AppendToResponseBody("<html><head><title>Not Found</title></head><body><h1>404 Not Found</h1></body></html>");
                response->SetStatusCode(404);
                response->SetHeader("content-type", "text/html");
            }
        }
        
        //TODO: implement persistent connections
        response->SetHeader("connection", "close");

        return response;
    }
}
}
}