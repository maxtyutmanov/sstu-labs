#include "Base64Utility.h"
#include <sstream>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <cmath>

using namespace std;
using namespace boost::archive::iterators;

namespace JustServer {
namespace Utility {

    bool Base64Utility::TryDecodeBase64(string encoded, string& decoded) {
        //remove padding characters (all '=' at the end of encoded string)
        size_t paddingCharsCount = 0;

        {
            string::size_type padChIndex = encoded.find_first_of('=');

            if (padChIndex != string::npos) {
                paddingCharsCount = encoded.size() - padChIndex;
                encoded.erase(padChIndex, paddingCharsCount);
            }
        }

        //get binary values of base64 characters received (e.g. A ~ 0, B ~ 1,...)

        stringstream binaryBase64Stream;

        try {
            copy(
                binary_from_base64<const char*>(encoded.c_str()),
                binary_from_base64<const char*>(encoded.c_str() + encoded.size()),
                ostream_iterator<char>(binaryBase64Stream));
        }
        catch (const dataflow_exception& ex) {
            return false;
        }

        string binaryBase64 = binaryBase64Stream.str();

        //add padding bytes (zero bytes, not '=' values!!!)

        for (size_t i = 0; i < paddingCharsCount; ++i) {
            binaryBase64.push_back('\0');
        }

        //transform 6-bit integers to 8-bit integers

        stringstream decodedStream;

        try {
            copy(
                transform_width<const char*, 8, 6>(binaryBase64.c_str()),
                transform_width<const char*, 8, 6>(binaryBase64.c_str() + binaryBase64.size()),
                ostream_iterator<char>(decodedStream));
        }
        catch (const dataflow_exception& ex) {
            return false;
        }

        decoded = decodedStream.str();

        for (size_t i = 0; i < paddingCharsCount; ++i) {
            decoded.erase(decoded.size() - 1, 1);
        }

        return true;
    }

}
}