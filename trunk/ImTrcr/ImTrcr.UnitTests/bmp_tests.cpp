#define BOOST_TEST_MODULE ImTrcrTests
#include <boost/test/unit_test.hpp>
#include <WinBMP.h>
#include <PointOutOfBitmapException.h>
#include <sstream>
#include <string>

using namespace std;
using namespace ImTrcr::Imaging;

//template <image_size_t x, image_size_t y>
//bool is_valid_point_exception(const PointOutOfBitmapException& ex) {
//    return ex.GetX() == x && ex.GetY() == y;
//}

BOOST_AUTO_TEST_SUITE(bitmap_tests)

BOOST_AUTO_TEST_CASE(ctor_getwidth_getheight) {
    WinBMP bmp(200, 200);

    BOOST_CHECK(bmp.GetHeight() == 200);
    BOOST_CHECK(bmp.GetWidth() == 200);
}

BOOST_AUTO_TEST_CASE(getpixel_valid) {
    WinBMP bmp(200, 200);

    RGBTriple px = bmp.GetPixel(0, 0);
    
    BOOST_CHECK(px.blue == 0);
    BOOST_CHECK(px.green == 0);
    BOOST_CHECK(px.red == 0);
}

BOOST_AUTO_TEST_CASE(getpixel_invalid_coords) {
    WinBMP bmp(200, 300);

    BOOST_CHECK_THROW(RGBTriple px = bmp.GetPixel(200, 299), PointOutOfBitmapException);
}

BOOST_AUTO_TEST_CASE(setpixel_valid) {
    WinBMP bmp(200, 300);

    bmp.SetPixel(2, 3, RGBTriple(127, 128, 129));

    RGBTriple px = bmp.GetPixel(2, 3);

    BOOST_CHECK(px.red == 127);
    BOOST_CHECK(px.green == 128);
    BOOST_CHECK(px.blue == 129);
}

BOOST_AUTO_TEST_CASE(setpixel_invalid_coords) {
    WinBMP bmp(200, 300);

    BOOST_CHECK_THROW(bmp.SetPixel(200, 303, RGBTriple(20, 150, 10)), PointOutOfBitmapException);
}

BOOST_AUTO_TEST_CASE(get_color_depth) {
    WinBMP bmp(1000, 2000, 24);

    BOOST_CHECK(bmp.GetColorDepth() == 24);
}

BOOST_AUTO_TEST_CASE(to_stream) {
    WinBMP bmp(200, 300);

    ostringstream oss(ios::out|ios::binary);

    bmp.ToStream(oss);

    string serialized = oss.str();

    BOOST_CHECK(serialized.size() > 200 * 300 * bmp.GetColorDepth());
    BOOST_ASSERT(serialized.size() >= 2);
    BOOST_CHECK(serialized[0] == 'B');
    BOOST_CHECK(serialized[1] == 'M');
}

BOOST_AUTO_TEST_CASE(clone) {
    WinBMP original(1050, 1050);
    original.SetPixel(1000, 1000, RGBTriple(200, 100, 10));

    WinBMP copy = original.Clone();

    BOOST_CHECK(original.GetColorDepth() == copy.GetColorDepth());
    BOOST_CHECK(original.GetWidth() == copy.GetWidth());
    BOOST_CHECK(original.GetHeight() == copy.GetHeight());

    for (image_size_t x = 0; x < original.GetWidth(); ++x) {
        for (image_size_t y = 0; y < original.GetHeight(); ++y) {
            BOOST_ASSERT(original.GetPixel(x, y) == copy.GetPixel(x, y));
        }
    }

    copy.SetPixel(1000, 1000, RGBTriple(50, 50, 50));

    BOOST_CHECK(original.GetPixel(1000, 1000) == RGBTriple(200, 100, 10));
    BOOST_CHECK(copy.GetPixel(1000, 1000) == RGBTriple(50, 50, 50));
}

BOOST_AUTO_TEST_CASE(from_file) {
    WinBMP bmp = WinBMP::FromFile(L"тест.bmp");

    BOOST_CHECK(bmp.GetWidth() == 60);
    BOOST_CHECK(bmp.GetHeight() == 40);

    for (image_size_t x = 0; x < bmp.GetWidth(); ++x) {
        for (image_size_t y = 0; y < bmp.GetHeight(); ++y) {
            RGBTriple px = bmp.GetPixel(x, y);

            if (17 <= x && x <= 50 &&
                23 <= y && y <= 30) {

                BOOST_CHECK(px.red == 0 && px.green == 0 && px.blue == 0);
            }
            else {
                BOOST_CHECK(px.red == 255 && px.green == 255 && px.blue == 255);
            }
        }
    }
}

BOOST_AUTO_TEST_SUITE_END();