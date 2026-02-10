#pragma once
#include "stdafx.h"
#include <string>
#include <map>

struct ExifData
{
    std::wstring aperture;
    std::wstring iso;
    std::wstring shutterSpeed;
    std::wstring manufacturer;
    std::wstring model;
};

class ExifReader
{
public:
    ExifReader();
    ~ExifReader();
    
    bool ReadExifData(const std::wstring& filePath, ExifData& exifData);
    
private:
    std::wstring GetPropertyItemAsString(Gdiplus::Image* image, PROPID propId);
    std::wstring GetPropertyItemAsRational(Gdiplus::Image* image, PROPID propId);
    std::wstring FormatAperture(const std::wstring& value);
    std::wstring FormatShutterSpeed(const std::wstring& value);
};
