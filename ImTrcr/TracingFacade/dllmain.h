#pragma once

enum ConvertionStatus {
    OK = 0,
    UNSUPPORTED_FORMAT = -1,
    INVALID_STREAM = -2
};

//Converts original raster image to the vector one in SVG format. 
//Returns status code and XML encoded in UTF-8
int ConvertToSvg(unsigned char* sourceImageBytes, unsigned long sourceSize, unsigned char* svgXml, unsigned long* serializedSize);