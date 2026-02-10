#include "stdafx.h"
#include "ImageProcessor.h"
#include <sstream>

ImageProcessor::ImageProcessor()
{
}

ImageProcessor::~ImageProcessor()
{
}

CLSID ImageProcessor::GetEncoderClsid(const WCHAR* format)
{
    UINT num = 0;
    UINT size = 0;
    
    Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;
    
    Gdiplus::GetImageEncodersSize(&num, &size);
    if (size == 0)
        return CLSID_NULL;
    
    pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
    if (pImageCodecInfo == NULL)
        return CLSID_NULL;
    
    GetImageEncoders(num, size, pImageCodecInfo);
    
    for (UINT j = 0; j < num; ++j)
    {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
        {
            CLSID clsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return clsid;
        }
    }
    
    free(pImageCodecInfo);
    return CLSID_NULL;
}

std::wstring ImageProcessor::BuildWatermarkText(const ExifData& exifData, const WatermarkConfig& config)
{
    std::wostringstream oss;
    bool first = true;
    
    if (config.showAperture && !exifData.aperture.empty())
    {
        oss << exifData.aperture;
        first = false;
    }
    
    if (config.showISO && !exifData.iso.empty())
    {
        if (!first) oss << L"  ";
        oss << exifData.iso;
        first = false;
    }
    
    if (config.showShutterSpeed && !exifData.shutterSpeed.empty())
    {
        if (!first) oss << L"  ";
        oss << exifData.shutterSpeed;
    }
    
    return oss.str();
}

void ImageProcessor::DrawLogo(Gdiplus::Graphics& graphics, const std::wstring& manufacturer, 
                              int x, int y, int height)
{
    // Create a simple text-based logo for manufacturer
    // In a real implementation, you would load actual logo images
    std::wstring logoText;
    
    if (manufacturer.find(L"NIKON") != std::wstring::npos || 
        manufacturer.find(L"Nikon") != std::wstring::npos)
    {
        logoText = L"NIKON";
    }
    else if (manufacturer.find(L"Canon") != std::wstring::npos ||
             manufacturer.find(L"CANON") != std::wstring::npos)
    {
        logoText = L"Canon";
    }
    else if (manufacturer.find(L"Sony") != std::wstring::npos ||
             manufacturer.find(L"SONY") != std::wstring::npos)
    {
        logoText = L"SONY";
    }
    else
    {
        logoText = manufacturer;
    }
    
    if (!logoText.empty())
    {
        Gdiplus::FontFamily fontFamily(L"Arial");
        Gdiplus::Font font(&fontFamily, (Gdiplus::REAL)height, FontStyleBold, UnitPixel);
        Gdiplus::SolidBrush brush(Gdiplus::Color(255, 255, 255, 255));
        
        graphics.DrawString(logoText.c_str(), -1, &font, 
                          Gdiplus::PointF((Gdiplus::REAL)x, (Gdiplus::REAL)y), &brush);
    }
}

void ImageProcessor::DrawWatermark(Gdiplus::Graphics& graphics, const ExifData& exifData, 
                                  const WatermarkConfig& config, int imageWidth, int imageHeight)
{
    std::wstring watermarkText = BuildWatermarkText(exifData, config);
    
    if (watermarkText.empty())
        return;
    
    // Set up text rendering
    Gdiplus::FontFamily fontFamily(L"Segoe UI");
    int fontSize = imageHeight / 40;  // Adjust font size based on image height
    if (fontSize < 12) fontSize = 12;
    
    Gdiplus::Font font(&fontFamily, (Gdiplus::REAL)fontSize, FontStyleRegular, UnitPixel);
    Gdiplus::SolidBrush textBrush(Gdiplus::Color(255, 255, 255, 255));
    Gdiplus::SolidBrush shadowBrush(Gdiplus::Color(180, 0, 0, 0));
    
    // Measure text
    Gdiplus::RectF layoutRect(0, 0, (Gdiplus::REAL)imageWidth, (Gdiplus::REAL)imageHeight);
    Gdiplus::RectF boundingBox;
    graphics.MeasureString(watermarkText.c_str(), -1, &font, layoutRect, &boundingBox);
    
    // Calculate position
    int margin = 20;
    int x = margin;
    int y;
    
    if (config.position == WatermarkPosition::Top)
    {
        y = margin;
    }
    else
    {
        y = imageHeight - (int)boundingBox.Height - margin;
    }
    
    // Draw logo first
    if (!exifData.manufacturer.empty())
    {
        int logoHeight = fontSize;
        DrawLogo(graphics, exifData.manufacturer, x, y, logoHeight);
        x += (int)boundingBox.Height * 3;  // Offset for logo width
    }
    
    // Draw shadow
    graphics.DrawString(watermarkText.c_str(), -1, &font, 
                       Gdiplus::PointF((Gdiplus::REAL)(x + 2), (Gdiplus::REAL)(y + 2)), 
                       &shadowBrush);
    
    // Draw text
    graphics.DrawString(watermarkText.c_str(), -1, &font, 
                       Gdiplus::PointF((Gdiplus::REAL)x, (Gdiplus::REAL)y), 
                       &textBrush);
}

bool ImageProcessor::ProcessImage(const std::wstring& inputPath, const std::wstring& outputPath, 
                                  const WatermarkConfig& config)
{
    // Read EXIF data
    ExifData exifData;
    if (!m_exifReader.ReadExifData(inputPath, exifData))
        return false;
    
    // Load the image
    Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(inputPath.c_str());
    if (pBitmap->GetLastStatus() != Gdiplus::Ok)
    {
        delete pBitmap;
        return false;
    }
    
    int width = pBitmap->GetWidth();
    int height = pBitmap->GetHeight();
    
    // Create a new bitmap with the same size
    Gdiplus::Bitmap* pOutputBitmap = new Gdiplus::Bitmap(width, height, PixelFormat24bppRGB);
    
    // Create graphics object
    Gdiplus::Graphics graphics(pOutputBitmap);
    graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
    graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
    
    // Draw the original image
    graphics.DrawImage(pBitmap, 0, 0, width, height);
    
    // Draw watermark
    DrawWatermark(graphics, exifData, config, width, height);
    
    // Save the image with high quality
    CLSID jpegClsid = GetEncoderClsid(L"image/jpeg");
    
    // Set JPEG quality to maximum
    Gdiplus::EncoderParameters encoderParams;
    encoderParams.Count = 1;
    encoderParams.Parameter[0].Guid = Gdiplus::EncoderQuality;
    encoderParams.Parameter[0].Type = Gdiplus::EncoderParameterValueTypeLong;
    encoderParams.Parameter[0].NumberOfValues = 1;
    ULONG quality = 100;
    encoderParams.Parameter[0].Value = &quality;
    
    Gdiplus::Status status = pOutputBitmap->Save(outputPath.c_str(), &jpegClsid, &encoderParams);
    
    delete pBitmap;
    delete pOutputBitmap;
    
    return status == Gdiplus::Ok;
}
