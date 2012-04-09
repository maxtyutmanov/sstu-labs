#include "WinBmpColorTable.h"
#include "InvalidBmpStreamException.h"

using namespace std;

namespace ImTrcr {
namespace Imaging {

    ArgbQuad WinBmpColorTable::GetColor(byte* dataPtr) const {
        ArgbQuad color;

        if (bitsPerPixel == 32) {
            color.blue = *dataPtr;
            color.green = *(dataPtr + 1);
            color.red = *(dataPtr + 2);
            color.alpha = *(dataPtr + 3);
        }
        else if (bitsPerPixel == 24) {
            color.blue = *dataPtr;
            color.green = *(dataPtr + 1);
            color.red = *(dataPtr + 2);
        }
        else if (bitsPerPixel == 8) {
            byte colorIndex = *dataPtr;

            if (0 < colorIndex && colorIndex < table.size()) {
                color = table[colorIndex];
            }
        }

        return color;
    }

    WinBmpColorTable* WinBmpColorTable::FromStream(byte bitsPerPixel, unsigned long numberOfColors, std::istream& input) {
        if (bitsPerPixel == 8) {
            //read color table

            if (!input.good()) {
                throw InvalidBmpStreamException("Cannot read color table from the given stream. input.good() == false");
            }

            byte* colorTableBuffer = new byte[sizeof(ArgbQuad) * numberOfColors];

            input.read((char *)colorTableBuffer, sizeof(ArgbQuad) * numberOfColors);

            if (!input.good()) {
                delete[] colorTableBuffer;
                throw InvalidBmpStreamException("Cannot read color table from the given stream. input.good() == false");
            }

            vector<ArgbQuad> colorTable;
            colorTable.resize(numberOfColors);

            byte* bufferPtr = colorTableBuffer;

            for (size_t i = 0; i < numberOfColors; ++i) {
                colorTable[i].blue = *bufferPtr;
                colorTable[i].green = *(bufferPtr + 1);
                colorTable[i].red = *(bufferPtr + 2);
                colorTable[i].alpha = *(bufferPtr + 3);

                bufferPtr += sizeof(ArgbQuad);
            }

            delete[] colorTableBuffer;

            return new WinBmpColorTable(bitsPerPixel, colorTable);
        }
        else if (bitsPerPixel == 24) {
            return new WinBmpColorTable(bitsPerPixel, vector<ArgbQuad>());
        }
        else {
            throw InvalidBmpStreamException("Bitmap format is not supported");
        }
    }

    WinBmpColorTable::WinBmpColorTable(byte bitsPerPixel, const std::vector<ArgbQuad>& colorTable) {
        this->bitsPerPixel = bitsPerPixel;
        this->table = colorTable;
    }
}
}