#include "EncodingUtility.h"
#include <Windows.h>

using namespace std;

namespace JustServer {
namespace Utility {

    wstring EncodingUtility::Utf8ToWideChar(const string& utf8string) {
        //get required buffer size
        int bufferLength = MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), utf8string.length() + 1, NULL, 0);

        wchar_t* multibyteStr = new wchar_t[bufferLength];

        MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), utf8string.length() + 1, multibyteStr, bufferLength);

        return wstring(multibyteStr);
    }

}
}