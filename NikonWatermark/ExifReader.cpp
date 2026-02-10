#include "stdafx.h"
#include "ExifReader.h"
#include <sstream>
#include <iomanip>

ExifReader::ExifReader()
{
}

ExifReader::~ExifReader()
{
}

std::wstring ExifReader::GetPropertyItemAsString(Gdiplus::Image* image, PROPID propId)
{
    UINT size = image->GetPropertyItemSize(propId);
    if (size == 0)
        return L"";
    
    std::vector<BYTE> buffer(size);
    Gdiplus::PropertyItem* pItem = (Gdiplus::PropertyItem*)&buffer[0];
    
    if (image->GetPropertyItem(propId, size, pItem) != Gdiplus::Ok)
        return L"";
    
    if (pItem->type == PropertyTagTypeASCII)
    {
        std::string str((char*)pItem->value);
        return std::wstring(str.begin(), str.end());
    }
    
    return L"";
}

std::wstring ExifReader::GetPropertyItemAsRational(Gdiplus::Image* image, PROPID propId)
{
    UINT size = image->GetPropertyItemSize(propId);
    if (size == 0)
        return L"";
    
    std::vector<BYTE> buffer(size);
    Gdiplus::PropertyItem* pItem = (Gdiplus::PropertyItem*)&buffer[0];
    
    if (image->GetPropertyItem(propId, size, pItem) != Gdiplus::Ok)
        return L"";
    
    if (pItem->type == PropertyTagTypeRational)
    {
        UINT* rational = (UINT*)pItem->value;
        if (rational[1] != 0)
        {
            double value = (double)rational[0] / (double)rational[1];
            std::wostringstream oss;
            oss << std::fixed << std::setprecision(1) << value;
            return oss.str();
        }
    }
    
    return L"";
}

std::wstring ExifReader::FormatAperture(const std::wstring& value)
{
    if (value.empty())
        return L"";
    
    double aperture = _wtof(value.c_str());
    std::wostringstream oss;
    oss << L"f/" << std::fixed << std::setprecision(1) << aperture;
    return oss.str();
}

std::wstring ExifReader::FormatShutterSpeed(const std::wstring& value)
{
    if (value.empty())
        return L"";
    
    double speed = _wtof(value.c_str());
    
    if (speed < 1.0)
    {
        std::wostringstream oss;
        oss << L"1/" << (int)(1.0 / speed);
        return oss.str();
    }
    else
    {
        std::wostringstream oss;
        oss << std::fixed << std::setprecision(1) << speed << L"s";
        return oss.str();
    }
}

bool ExifReader::ReadExifData(const std::wstring& filePath, ExifData& exifData)
{
    Gdiplus::Image image(filePath.c_str());
    
    if (image.GetLastStatus() != Gdiplus::Ok)
        return false;
    
    // Read manufacturer
    exifData.manufacturer = GetPropertyItemAsString(&image, PropertyTagEquipMake);
    
    // Read model
    exifData.model = GetPropertyItemAsString(&image, PropertyTagEquipModel);
    
    // Read aperture (F-Number)
    std::wstring aperture = GetPropertyItemAsRational(&image, PropertyTagExifFNumber);
    exifData.aperture = FormatAperture(aperture);
    
    // Read ISO
    UINT size = image.GetPropertyItemSize(PropertyTagExifISOSpeed);
    if (size > 0)
    {
        std::vector<BYTE> buffer(size);
        Gdiplus::PropertyItem* pItem = (Gdiplus::PropertyItem*)&buffer[0];
        
        if (image.GetPropertyItem(PropertyTagExifISOSpeed, size, pItem) == Gdiplus::Ok)
        {
            if (pItem->type == PropertyTagTypeShort)
            {
                USHORT* iso = (USHORT*)pItem->value;
                std::wostringstream oss;
                oss << L"ISO " << *iso;
                exifData.iso = oss.str();
            }
        }
    }
    
    // Read shutter speed (exposure time)
    std::wstring shutter = GetPropertyItemAsRational(&image, PropertyTagExifExposureTime);
    exifData.shutterSpeed = FormatShutterSpeed(shutter);
    
    return true;
}
