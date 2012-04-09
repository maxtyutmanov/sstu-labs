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

    WinBMP::WinBMP(image_size_t width, image_size_t height, byte* bmpData, WinBmpColorTable* colorTable, byte bitsPerPixel) 
        : RasterImage(width, height) {

        assert(colorTable != NULL);
        assert(bmpData != NULL);

        this->bmpData = bmpData;
        this->colorTable = colorTable;
        this->bitsPerPixel = bitsPerPixel;
    }

    WinBMP::~WinBMP() {
        delete colorTable;
        delete[] bmpData;
    }

    ArgbQuad WinBMP::GetColor(image_size_t x, image_size_t y) const {
        byte bytesPerPixel = bitsPerPixel / 8;

        byte paddingBytes = bytesPerPixel * GetWidth() % sizeof(DWORD);

        image_size_t rowIndex = (GetHeight() - 1) - y;
        image_size_t rowOffset = x * bytesPerPixel;

        byte* dataPtr = bmpData + (rowIndex * (GetWidth() * bytesPerPixel + paddingBytes) + rowOffset);

        return colorTable->GetColor(dataPtr);
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

        //read bmp info

        BITMAPINFOHEADER bmpInfoH;
        memset(&bmpInfoH, 0, sizeof(BITMAPINFOHEADER));
        input.read((char *)&bmpInfoH, sizeof(BITMAPINFOHEADER));

        if (!input.good()) {
            throw InvalidBmpStreamException("Cannot read BITMAPINFOHEADER from the given stream. input.good() == false");
        }

        //read color table

        input.seekg(sizeof(BITMAPFILEHEADER) + bmpInfoH.biSize, ios::beg);

        if (!input.good()) {
            throw InvalidBmpStreamException("Cannot read color table from the given stream. input.good() == false");
        }

        WinBmpColorTable* colorTable = WinBmpColorTable::FromStream(bmpInfoH.biBitCount, bmpInfoH.biClrUsed, input);

        //set stream position to image data and read it

        input.seekg(bmpFileH.bfOffBits, ios::beg);

        if (!input.good()) {
            throw InvalidBmpStreamException("Cannot read image data from the given stream. input.good() == false");
        }

        size_t bufferSize = bmpFileH.bfSize - bmpFileH.bfOffBits;

        byte* imageData = new byte[bufferSize];

        input.read((char *)imageData, bufferSize);

        //convert image data to RGB triples

        return WinBMP(bmpInfoH.biWidth, bmpInfoH.biHeight, imageData, colorTable, bmpInfoH.biBitCount);
    }
}
}