#pragma once
#include "stdafx.h"
#include "ExifReader.h"
#include <string>

enum class WatermarkPosition
{
    Top,
    Bottom
};

struct WatermarkConfig
{
    bool showAperture = true;
    bool showISO = true;
    bool showShutterSpeed = true;
    WatermarkPosition position = WatermarkPosition::Bottom;
};

class ImageProcessor
{
public:
    ImageProcessor();
    ~ImageProcessor();
    
    bool ProcessImage(const std::wstring& inputPath, const std::wstring& outputPath, const WatermarkConfig& config);
    
private:
    ExifReader m_exifReader;
    
    void DrawWatermark(Gdiplus::Graphics& graphics, const ExifData& exifData, 
                      const WatermarkConfig& config, int imageWidth, int imageHeight);
    void DrawLogo(Gdiplus::Graphics& graphics, const std::wstring& manufacturer, 
                 int x, int y, int height);
    std::wstring BuildWatermarkText(const ExifData& exifData, const WatermarkConfig& config);
    
    CLSID GetEncoderClsid(const WCHAR* format);
};
