#include "dllmain.h"
#include <WinBMP.h>
#include <PotraceTracer.h>
#include <SvgSerializer.h>

#include <stdexcept>
#include <sstream>

using namespace std;
using namespace ImTrcr;

void CleanUp(Vectorization::ITracer* pTracer, Imaging::VectorImage* pVectorImage, Imaging::ISvgSerializer* pSvgSerializer, TiXmlDocument* pSerializedSvgXml);

int ConvertToSvg(unsigned char* sourceImageBytes, unsigned long sourceSize, unsigned char* svgXml, unsigned long* serializedSize) {

    Vectorization::ITracer* pTracer = NULL;
    Imaging::VectorImage* pVectorImage = NULL;
    Imaging::ISvgSerializer* pSvgSerializer = NULL;
    TiXmlDocument* pSerializedSvgXml = NULL;

    try {
        //prepare input stream

        string sourceBuffer;
        sourceBuffer.resize(sourceSize);

        for (unsigned long i = 0; i < sourceSize; ++i) {
            sourceBuffer[i] = sourceImageBytes[i];
        }

        istringstream sourceStream(sourceBuffer);

        //create bitmap
        Imaging::WinBMP bmp = Imaging::WinBMP::FromStream(sourceStream);

        //trace bitmap
        pTracer = new Vectorization::PotraceTracer();
        pVectorImage = pTracer->Trace(bmp);

        //serialize vector image to SVG XML document
        pSvgSerializer = new Imaging::SvgSerializer();
        pSerializedSvgXml = pSvgSerializer->Serialize(*pVectorImage);

        TiXmlPrinter xmlPrinter;
        pSerializedSvgXml->Accept(&xmlPrinter);
        *serializedSize = xmlPrinter.Size();
        svgXml = (unsigned char *)xmlPrinter.CStr();
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