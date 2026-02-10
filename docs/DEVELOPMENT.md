# NikonWatermark Development Guide

## Architecture Overview

NikonWatermark is built using Win32 API with the Windows Template Library (WTL) framework. The application follows a modular design with clear separation of concerns.

### Project Structure

```
NikonWatermark/
├── NikonWatermark.sln          # Visual Studio solution file
└── NikonWatermark/
    ├── main.cpp                # Application entry point
    ├── MainFrame.h/cpp         # Main window and UI logic
    ├── ExifReader.h/cpp        # EXIF metadata reading
    ├── ImageProcessor.h/cpp    # Image processing and watermarking
    ├── resource.h              # Resource IDs
    ├── NikonWatermark.rc       # Resource file
    ├── stdafx.h                # Precompiled headers
    └── NikonWatermark.vcxproj  # Project file
```

## Components

### 1. main.cpp
- **Purpose**: Application entry point
- **Responsibilities**:
  - Initialize GDI+ for image processing
  - Initialize COM and Common Controls
  - Set up WTL message loop
  - Create and display main window

### 2. MainFrame (MainFrame.h/cpp)
- **Purpose**: Main application window and UI controller
- **Key Features**:
  - Dark theme implementation via WM_CTLCOLOR messages
  - Dual list box layout (import/export)
  - Configuration controls (checkboxes, combo box)
  - File dialog integration
  - Image processing workflow coordination

**Key Methods**:
- `OnCreate()`: Creates all UI controls and sets up layout
- `OnImportImages()`: Handles multi-file selection
- `OnProcessImages()`: Coordinates batch image processing
- `SetDarkTheme()`: Applies dark color scheme
- `UpdateLayout()`: Responsive layout management

### 3. ExifReader (ExifReader.h/cpp)
- **Purpose**: Read and parse EXIF metadata from images
- **Key Features**:
  - Reads camera manufacturer and model
  - Extracts aperture, ISO, and shutter speed
  - Formats values for display

**Key Methods**:
- `ReadExifData()`: Main method to extract all EXIF data
- `GetPropertyItemAsString()`: Read string-type EXIF tags
- `GetPropertyItemAsRational()`: Read rational-type EXIF tags (for aperture/shutter)
- `FormatAperture()`: Format aperture as "f/X.X"
- `FormatShutterSpeed()`: Format shutter speed as "1/XXX" or "X.Xs"

**EXIF Property IDs Used**:
```cpp
PropertyTagEquipMake         // 0x010F - Manufacturer
PropertyTagEquipModel        // 0x0110 - Camera model
PropertyTagExifFNumber       // 0x829D - Aperture
PropertyTagExifISOSpeed      // 0x8827 - ISO
PropertyTagExifExposureTime  // 0x829A - Shutter speed
```

### 4. ImageProcessor (ImageProcessor.h/cpp)
- **Purpose**: Process images and apply watermarks
- **Key Features**:
  - Load images using GDI+
  - Render watermark text with shadow
  - Display camera manufacturer logo
  - Save with maximum JPEG quality

**Key Methods**:
- `ProcessImage()`: Main processing pipeline
- `DrawWatermark()`: Render watermark on image
- `DrawLogo()`: Render manufacturer logo
- `BuildWatermarkText()`: Construct EXIF text string
- `GetEncoderClsid()`: Get JPEG encoder for saving

**Image Processing Flow**:
1. Read EXIF data via ExifReader
2. Load source image into GDI+ Bitmap
3. Create output bitmap
4. Draw original image onto output
5. Render watermark (logo + text)
6. Save with high quality JPEG encoding

## Dark Theme Implementation

The dark theme is implemented using Windows message handling:

```cpp
LRESULT OnCtlColorStatic(...)  // For static text controls
{
    SetTextColor(hdc, RGB(220, 220, 220));  // Light gray text
    SetBkColor(hdc, RGB(30, 30, 30));       // Dark background
    return (LRESULT)m_hBrushDark;
}

LRESULT OnCtlColorListBox(...)  // For list boxes
{
    SetTextColor(hdc, RGB(220, 220, 220));
    SetBkColor(hdc, RGB(45, 45, 45));       // Slightly lighter for controls
    return (LRESULT)m_hBrushDarkControl;
}
```

**Color Scheme**:
- Background: RGB(30, 30, 30) - Dark gray
- Controls: RGB(45, 45, 45) - Medium gray
- Text: RGB(220, 220, 220) - Light gray

## Building the Project

### Prerequisites
1. Visual Studio 2022 (or later)
2. C++ Desktop Development workload
3. Windows 10 SDK (10.0.19041.0 or later)
4. WTL (included with ATL/MFC in Visual Studio)

### Build Steps

**Debug Build**:
```bash
# Command line
msbuild NikonWatermark.sln /p:Configuration=Debug /p:Platform=x64

# Or in Visual Studio
Ctrl+Shift+B (Build Solution)
F5 (Build and Run)
```

**Release Build**:
```bash
msbuild NikonWatermark.sln /p:Configuration=Release /p:Platform=x64
```

### Project Configuration

**Compiler Settings**:
- Character Set: Unicode
- Warning Level: Level 3
- Conformance Mode: Yes
- Include Directories: $(ProjectDir)

**Linker Settings**:
- Subsystem: Windows
- Additional Dependencies: comctl32.lib, gdiplus.lib

## Adding New Features

### Adding a New EXIF Field

1. **Update ExifData structure** (ExifReader.h):
```cpp
struct ExifData
{
    std::wstring aperture;
    std::wstring iso;
    std::wstring shutterSpeed;
    std::wstring focalLength;  // New field
    // ...
};
```

2. **Read the field** (ExifReader.cpp):
```cpp
bool ExifReader::ReadExifData(...)
{
    // ... existing code ...
    
    // Read focal length
    exifData.focalLength = GetPropertyItemAsRational(&image, PropertyTagExifFocalLength);
    
    return true;
}
```

3. **Add UI control** (MainFrame.cpp):
```cpp
m_focalLengthCheck.Create(m_hWnd, NULL, L"Show Focal Length", 
    WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 
    0, IDC_EXIF_FOCAL_LENGTH);
```

4. **Update watermark text** (ImageProcessor.cpp):
```cpp
std::wstring ImageProcessor::BuildWatermarkText(...)
{
    // ... existing code ...
    
    if (config.showFocalLength && !exifData.focalLength.empty())
    {
        if (!first) oss << L"  ";
        oss << exifData.focalLength << L"mm";
    }
    
    return oss.str();
}
```

### Adding a New Camera Logo

Update `DrawLogo()` method in ImageProcessor.cpp:

```cpp
void ImageProcessor::DrawLogo(...)
{
    std::wstring logoText;
    
    if (manufacturer.find(L"Fujifilm") != std::wstring::npos)
    {
        logoText = L"FUJIFILM";
    }
    // ... existing brands ...
    
    // Render logo text
}
```

For actual logo images, replace text rendering with:
```cpp
Gdiplus::Image logoImage(L"logos\\nikon.png");
graphics.DrawImage(&logoImage, x, y, width, height);
```

## Testing

### Manual Testing Checklist

**UI Testing**:
- [ ] Window opens and displays correctly
- [ ] All controls are visible
- [ ] Dark theme applies to all controls
- [ ] Window resizing works properly
- [ ] List boxes scroll correctly

**Functionality Testing**:
- [ ] Import single image
- [ ] Import multiple images
- [ ] Process images with all EXIF fields enabled
- [ ] Process images with selective EXIF fields
- [ ] Test top position watermark
- [ ] Test bottom position watermark
- [ ] Verify output image quality

**EXIF Testing**:
- [ ] Test with Nikon photos
- [ ] Test with Canon photos
- [ ] Test with Sony photos
- [ ] Test with photos lacking EXIF data
- [ ] Test with various aperture values
- [ ] Test with various ISO values
- [ ] Test with various shutter speeds

**Error Handling**:
- [ ] Cancel import dialog
- [ ] Cancel output folder selection
- [ ] Process without importing images
- [ ] Handle corrupted images
- [ ] Handle insufficient disk space

## Code Style Guidelines

### Naming Conventions
- Classes: PascalCase (e.g., `ImageProcessor`)
- Methods: PascalCase (e.g., `ReadExifData()`)
- Member variables: m_prefix + camelCase (e.g., `m_importList`)
- Local variables: camelCase (e.g., `exifData`)
- Constants: UPPER_SNAKE_CASE (e.g., `MAX_PATH`)

### Comments
- Use `//` for single-line comments
- Document public methods with brief description
- Explain complex algorithms or non-obvious code

### Formatting
- Indent with 4 spaces (no tabs)
- Opening brace on same line for methods
- One statement per line
- Space after control keywords (if, for, while)

## Performance Considerations

### Memory Management
- Images are processed one at a time to minimize memory usage
- Bitmaps are properly deleted after use
- GDI+ objects have automatic cleanup via destructors

### Optimization Opportunities
- Use worker threads for batch processing
- Cache encoder CLSID instead of querying each time
- Reuse Graphics objects when processing multiple images

## Debugging

### Debug Output
Add trace statements:
```cpp
ATLTRACE(L"Processing image: %s\n", filePath.c_str());
```

### Common Issues

**Images not processing**:
- Check EXIF data is present using `image->GetPropertyItemSize()`
- Verify GDI+ status codes
- Ensure output folder is writable

**Watermark not visible**:
- Check text color contrasts with image
- Verify font is available
- Ensure watermark text is not empty

**Memory leaks**:
- Always delete GDI+ bitmaps
- Clean up brushes in OnDestroy
- Use RAII where possible

## Dependencies

### Required Libraries
- **GDI+** (gdiplus.lib): Image loading, processing, and saving
- **Common Controls** (comctl32.lib): List boxes and other controls
- **Shell API**: Folder browser dialog

### Windows SDK Components
- Windows.h: Core Win32 API
- CommCtrl.h: Common controls
- GdiPlus.h: GDI+ graphics API
- ShlObj.h: Shell objects (folder browser)

## Contributing

### Workflow
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

### Pull Request Guidelines
- Describe what the change does
- Include screenshots for UI changes
- Test on both Debug and Release builds
- Ensure code follows style guidelines
- Update documentation if needed

## Future Improvements

### Planned Features
1. **Custom watermark templates**: Allow users to define their own text format
2. **Logo image support**: Load actual brand logos from PNG files
3. **Font customization**: Let users choose font, size, and color
4. **PNG output**: Add PNG export option with transparency
5. **RAW support**: Process RAW image formats (CR2, NEF, ARW)
6. **Batch rename**: Automatically rename output files
7. **Preview**: Show watermark preview before processing
8. **Drag-and-drop**: Support dragging files into the window

### Technical Debt
- Refactor color constants into a theme manager
- Add error logging to file
- Implement proper exception handling
- Create unit tests for EXIF reading
- Add configuration file for persistent settings

## Resources

### Documentation
- [WTL Documentation](http://wtl.sourceforge.net/)
- [GDI+ Reference](https://docs.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-gdi-start)
- [Win32 API Reference](https://docs.microsoft.com/en-us/windows/win32/api/)
- [EXIF Specification](http://www.cipa.jp/std/documents/e/DC-008-2012_E.pdf)

### Tools
- Visual Studio 2022
- Spy++ (for UI debugging)
- Process Monitor (for file I/O debugging)
- Visual Studio Memory Profiler

## License

This project is licensed under the terms specified in the LICENSE file.
