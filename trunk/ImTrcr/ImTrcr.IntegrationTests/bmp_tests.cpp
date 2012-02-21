#define BOOST_TEST_MODULE ImTrcrTests
#include <boost/test/unit_test.hpp>
#include <WinBMP.h>
#include <PointOutOfBitmapException.h>
#include <sstream>
#include <string>

using namespace std;
using namespace ImTrcr::Imaging;

bool ImagesAreIdentical(const WinBMP& first, const WinBMP& second) {
    if (first.GetWidth() == second.GetWidth() &&
        first.GetHeight() == second.GetHeight() &&
        first.GetColorDepth() == second.GetColorDepth()) {

        for (image_size_t x = 0; x < first.GetWidth(); ++x) {
            for (image_size_t y = 0; y < first.GetHeight(); ++y) {
                if (first.GetPixel(x, y) != second.GetPixel(x, y)) {
                    return false;
                }
            }
        }

        return true;
    }
    else {
        return false;
    }
}

BOOST_AUTO_TEST_SUITE(bitmap_tests)

BOOST_AUTO_TEST_CASE(to_stream_and_then_from_stream) {
    WinBMP original(200, 300);

    original.SetPixel(1, 3, RGBTriple(255, 100, 200));

    ostringstream oss(ios::out|ios::binary);

    original.ToStream(oss);

    istringstream iss(oss.str(), ios::in|ios::binary);

    WinBMP restored = WinBMP::FromStream(iss);

    BOOST_CHECK(ImagesAreIdentical(original, restored));
}

BOOST_AUTO_TEST_SUITE_END();