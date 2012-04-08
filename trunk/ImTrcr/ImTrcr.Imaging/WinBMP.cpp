#pragma once

#include "WinBMP.h"
#include <Windows.h>
#include <fstream>
#include "FileNotFoundException.h"
#include "InvalidBmpStreamException.h"
#include <boost/filesystem.hpp>

using namespace std;

namespace ImTrcr {
namespace Imaging {

    WinBMP::WinBMP(image_size_t width, image_size_t height, unsigned short colorDepth) 
        : RasterImage(width, height, WinBMP::CreateDefaultPixelArray(width, height)) {

        SetColorDepth(colorDepth);
    }

    WinBMP::WinBMP(image_size_t width, image_size_t height, ArgbQuad* pixelArray, unsigned short colorDepth) 
        : RasterImage(width, height, pixelArray) {

        SetColorDepth(colorDepth);
    }

    ArgbQuad* WinBMP::CreateDefaultPixelArray(image_size_t width, image_size_t height) {
        if (width > 0 && height > 0) {
            return new ArgbQuad[width * height];
        }
        else {
            return NULL;
        }
    }

    unsigned short WinBMP::GetColorDepth() const {
        return colorDepth;
    }

    void WinBMP::ToStream(ostream& output) const {
        unsigned long imageDataLength;
        unsigned char* imageData = ConvertRGBBufferToBmpData(&imageDataLength);

        BITMAPFILEHEADER bmpFileH;
        memset(&bmpFileH, 0, sizeof(BITMAPFILEHEADER));
        bmpFileH.bfType = 0x4d42;       // 0x4d42 = 'BM'
        bmpFileH.bfReserved1 = bmpFileH.bfReserved2 = 0;
        bmpFileH.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        bmpFileH.bfSize = bmpFileH.bfOffBits + imageDataLength;
        
        BITMAPINFOHEADER bmpInfoH;
        memset(&bmpInfoH, 0, sizeof(BITMAPINFOHEADER));
        bmpInfoH.biSize = sizeof(BITMAPINFOHEADER);
        bmpInfoH.biWidth = width;
        bmpInfoH.biHeight = height;
        bmpInfoH.biPlanes = 1;
        bmpInfoH.biBitCount = GetColorDepth();
        bmpInfoH.biCompression = BI_RGB;
        bmpInfoH.biXPelsPerMeter = 0x0ec4;
        bmpInfoH.biYPelsPerMeter = 0x0ec4;
#pragma warning //the following code works only for 24 bit image. Wait... the WHOLE THING works only for 24 bit image!!!
        bmpInfoH.biClrUsed = 0;
        bmpInfoH.biClrImportant = 0;
        bmpInfoH.biSizeImage = 0;

        output.write((const char *)&bmpFileH, sizeof(BITMAPFILEHEADER));
        output.write((const char *)&bmpInfoH, sizeof(BITMAPINFOHEADER));
        output.write((const char *)imageData, imageDataLength);

        delete[] imageData;
    }

    WinBMP WinBMP::Clone() const {
        ArgbQuad* clonePxArray = new ArgbQuad[this->GetWidth() * this->GetHeight()];
        memcpy(clonePxArray, this->pixelArray, this->GetWidth() * this->GetHeight() * sizeof(ArgbQuad));

        return WinBMP(this->GetWidth(), this->GetHeight(), clonePxArray, this->GetColorDepth());
    }

    WinBMP WinBMP::FromFile(const wstring& path) {
        //check if file exists
        boost::filesystem3::path boostPath(path);
        if (!boost::filesystem3::exists(boostPath)) {
            throw FileNotFoundException(path);
        }

        ifstream input(path, ios::in|ios::binary);

        return WinBMP::FromStream(input);
    }

    WinBMP WinBMP::FromStream(istream& input) {
        //check the stream

        if (!input.good()) {
            throw InvalidBmpStreamException("Cannot read anything from the given stream. input.good() == false");
        }

        //read bmp file header

        BITMAPFILEHEADER bmpFileH;
        memset(&bmpFileH, 0, sizeof(BITMAPFILEHEADER));
        input.read((char *)&bmpFileH, sizeof(BITMAPFILEHEADER));

        if (!input.good()) {
            throw InvalidBmpStreamException("Cannot read BITMAPFILEHEADER from the given stream. input.good() == false");
        }

        //read bmp info header

        BITMAPINFOHEADER bmpInfoH;
        memset(&bmpInfoH, 0, sizeof(BITMAPINFOHEADER));
        input.read((char *)&bmpInfoH, sizeof(BITMAPINFOHEADER));

        if (!input.good()) {
            throw InvalidBmpStreamException("Cannot read BITMAPINFOHEADER from the given stream. input.good() == false");
        }

        //set stream position to image data and read it

        input.seekg(bmpFileH.bfOffBits, ios::beg);

        if (!input.good()) {
            throw InvalidBmpStreamException("Cannot read image data from the given stream. input.good() == false");
        }

        size_t bufferSize = bmpFileH.bfSize - bmpFileH.bfOffBits;

        unsigned char* imageData = new unsigned char[bufferSize];

        input.read((char *)imageData, bufferSize);

        //convert image data to RGB triples

        ArgbQuad* pxArray = WinBMP::ConvertBmpDataToRGBBuffer(imageData, bmpInfoH.biWidth, bmpInfoH.biHeight, bmpInfoH.biBitCount / 8);

        delete[] imageData;

        return WinBMP(bmpInfoH.biWidth, bmpInfoH.biHeight, pxArray, bmpInfoH.biBitCount);
    }

    ArgbQuad* WinBMP::ConvertBmpDataToRGBBuffer(unsigned char* data, image_size_t width, image_size_t height, unsigned short bytesPerPixel) {
        //calculate padding bytes count

        image_size_t widthInBytes = width * bytesPerPixel;
        image_size_t paddingBytes = widthInBytes % sizeof(DWORD);

        ArgbQuad* result = new ArgbQuad[width * height];

        unsigned char *dataPtr = data;

        for (image_size_t y = height - 1; y >= 0; --y) {
            for (image_size_t x = 0; x < width; ++x) {
                ArgbQuad& px = result[y * width + x];

                px.blue = *(dataPtr++);
                px.green = *(dataPtr++);
                px.red = *(dataPtr++);
            }

            for (image_size_t i = 0; i < paddingBytes; ++i) {
                ++dataPtr;
            }
        }

        return result;
    }

    unsigned char* WinBMP::ConvertRGBBufferToBmpData(OUT unsigned long *resultLength) const {
        image_size_t widthInBytes = width * GetColorDepth() / 8;
        image_size_t paddingBytes = widthInBytes % sizeof(DWORD);
        image_size_t heightInBytes = height * GetColorDepth();

        *resultLength = (widthInBytes + paddingBytes) * heightInBytes;

        unsigned char* result = new unsigned char[*resultLength];

        unsigned char* resultPtr = result;

        for (image_size_t y = height - 1; y >= 0; --y) {
            for (image_size_t x = 0; x < width; ++x) {
                //TODO: can be optimized: h * width can be taken out of the nested for
                ArgbQuad px = pixelArray[y * width + x];

                *(resultPtr++) = px.blue;
                *(resultPtr++) = px.green;
                *(resultPtr++) = px.red;
            }

            //filling the padding space with zeros (according to WinBMP's spec)
            for (size_t i = 0; i < paddingBytes; ++i) {
                *(resultPtr++) = 0;
            }
        }

        return result;
    }
}
}