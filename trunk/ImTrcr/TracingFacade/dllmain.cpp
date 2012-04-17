#include "dllmain.h"
#include <WinBMP.h>
#include <PotraceTracer.h>
#include <SvgSerializer.h>

#include <stdexcept>
#include <sstream>

using namespace std;
using namespace ImTrcr;

void CleanUp(Vectorization::ITracer* pTracer, Imaging::VectorImage* pVectorImage);

int ConvertToSvg(unsigned char* sourceImageBytes, unsigned long bytesCount, unsigned char* svgXml) {

    Vectorization::ITracer* pTracer = NULL;
    Imaging::VectorImage* pVectorImage = NULL;

    try {
        //prepare input stream

        string sourceBuffer;
        sourceBuffer.resize(bytesCount);

        for (unsigned long i = 0; i < bytesCount; ++i) {
            sourceBuffer[i] = sourceImageBytes[i];
        }

        istringstream sourceStream(sourceBuffer);

        //create bitmap
        Imaging::WinBMP bmp = Imaging::WinBMP::FromStream(sourceStream);

        //trace bitmap
        pTracer = new Vectorization::PotraceTracer();
        pVectorImage = pTracer->Trace(bmp);

        //serialize vector image to SVG XML document
    }
    catch (const runtime_error& ex) {
        CleanUp(pTracer, pVectorImage);
    }
    catch (...) {
        CleanUp(pTracer, pVectorImage);
    }
}

void CleanUp(Vectorization::ITracer* pTracer, Imaging::VectorImage* pVectorImage) {
    if (pTracer != NULL) {
        delete pTracer;
    }

    if (pVectorImage != NULL) {
        delete pVectorImage;
    }
}