#pragma once

//Converts original raster image to the vector one in SVG format. 
//Returns status code and XML encoded in UTF-8
int ConvertToSvg(unsigned char* sourceImageBytes, unsigned long bytesCount, unsigned char* svgXml);