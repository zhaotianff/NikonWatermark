# Migration Guide: From Win32 WTL to WPF/MVVM

This document explains the migration from the original Win32/WTL C++ implementation to the new WPF/MVVM C# implementation.

## Overview

The NikonWatermark application has been completely rewritten using modern .NET technologies:

| Aspect | Old (Win32/WTL) | New (WPF/MVVM) |
|--------|----------------|----------------|
| **Language** | C++ | C# |
| **Framework** | Win32 API + WTL | .NET 8 + WPF |
| **Architecture** | Event-driven | MVVM pattern |
| **UI Technology** | Windows Controls | XAML |
| **Image Processing** | GDI+ | WPF Imaging |
| **EXIF Reading** | GDI+ PropertyItem | MetadataExtractor library |
| **Build System** | MSBuild (C++) | MSBuild (.NET) / dotnet CLI |

## Why Migrate?

### Benefits of WPF/MVVM

1. **Modern Development**
   - C# is more productive than C++
   - Better tooling and debugging experience
   - Rich ecosystem with NuGet packages

2. **MVVM Architecture**
   - Clean separation of concerns
   - Easier to test and maintain
   - Better code organization

3. **Declarative UI**
   - XAML provides clear UI structure
   - Data binding reduces boilerplate code
   - Easier to customize and theme

4. **Cross-platform Potential**
   - Code can be shared with .NET MAUI for mobile/Mac
   - Easier to port to other platforms in the future

5. **Package Management**
   - NuGet makes dependency management simple
   - Easy to update libraries
   - Large ecosystem of available packages

## Architecture Comparison

### Win32/WTL Architecture

```
main.cpp (Entry point)
  └── CMainFrame (Window class)
      ├── Message handlers (OnCreate, OnSize, etc.)
      ├── Control initialization
      ├── Event handling
      └── Business logic
  └── ImageProcessor (Separate class)
  └── ExifReader (Separate class)
```

### WPF/MVVM Architecture

```
App.xaml (Entry point)
  └── MainWindow.xaml (View - XAML)
      └── MainViewModel (ViewModel)
          ├── Commands (ImportImagesCommand, ProcessImagesCommand)
          ├── Observable properties
          └── Business logic coordination
      └── Services
          ├── ImageProcessorService
          └── ExifReaderService
      └── Models
          ├── ExifData
          ├── WatermarkConfig
          └── ImageInfo
```

## Code Comparison

### Creating UI Controls

**Old (Win32/WTL):**
```cpp
m_importButton.Create(m_hWnd, rcDefault, L"Import Images", 
    WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, IDC_IMPORT_BUTTON);
```

**New (WPF/XAML):**
```xml
<Button Content="Import Images" 
        Command="{Binding ImportImagesCommand}"/>
```

### Handling User Actions

**Old (Win32/WTL):**
```cpp
LRESULT CMainFrame::OnImportImages(WORD, WORD, HWND, BOOL&)
{
    // File dialog code
    // Add to list
    return 0;
}
```

**New (WPF/MVVM):**
```csharp
[RelayCommand]
private void ImportImages()
{
    var openFileDialog = new OpenFileDialog { ... };
    if (openFileDialog.ShowDialog() == true)
    {
        // Add to ObservableCollection
    }
}
```

### Data Binding

**Old (Win32/WTL):**
```cpp
// Manual synchronization
m_importList.AddString(fileName.c_str());
// Update UI manually when data changes
```

**New (WPF/MVVM):**
```csharp
// Automatic synchronization via data binding
ImportedImages.Add(new ImageInfo { FileName = fileName });
// UI updates automatically
```

## File Structure Mapping

| Old File | New File | Purpose |
|----------|----------|---------|
| `main.cpp` | `App.xaml` / `App.xaml.cs` | Application entry point |
| `MainFrame.h/cpp` | `MainWindow.xaml` / `MainWindow.xaml.cs` | Main window |
| - | `ViewModels/MainViewModel.cs` | Business logic and state |
| `ExifReader.h/cpp` | `Services/ExifReaderService.cs` | EXIF reading |
| `ImageProcessor.h/cpp` | `Services/ImageProcessorService.cs` | Image processing |
| `resource.h` | `Models/*.cs` | Data structures |
| `NikonWatermark.rc` | `MainWindow.xaml` (styles) | UI resources |
| `stdafx.h` | - (not needed in C#) | Precompiled headers |

## Feature Parity

All features from the original version are implemented in the new version:

| Feature | Win32/WTL | WPF/MVVM |
|---------|-----------|----------|
| Import multiple images | ✅ | ✅ |
| Display imported files list | ✅ | ✅ |
| Read EXIF data (Aperture, ISO, Shutter) | ✅ | ✅ |
| Camera manufacturer detection | ✅ | ✅ |
| Toggle EXIF fields | ✅ | ✅ |
| Position selection (Top/Bottom) | ✅ | ✅ |
| Process images with watermark | ✅ | ✅ |
| Export results list | ✅ | ✅ |
| Dark theme UI | ✅ | ✅ |
| High-quality JPEG output | ✅ | ✅ |

## Key Differences

### 1. EXIF Reading

**Old:** Used GDI+ PropertyItem API
```cpp
PropertyItem* propertyItem = NULL;
image->GetPropertyItem(PropertyTagFNumber, size, propertyItem);
```

**New:** Uses MetadataExtractor library
```csharp
var directories = ImageMetadataReader.ReadMetadata(filePath);
var exifData = directories.OfType<ExifSubIfdDirectory>().FirstOrDefault();
```

### 2. Image Processing

**Old:** GDI+ Graphics and Bitmap classes
```cpp
Graphics graphics(bitmap);
graphics.DrawImage(image, 0, 0);
```

**New:** WPF DrawingVisual and RenderTargetBitmap
```csharp
var drawingVisual = new DrawingVisual();
using (var dc = drawingVisual.RenderOpen())
{
    dc.DrawImage(originalImage, rect);
}
```

### 3. UI Updates

**Old:** Manual invalidation
```cpp
m_importList.Invalidate();
UpdateWindow();
```

**New:** Automatic via INotifyPropertyChanged
```csharp
[ObservableProperty]
private ObservableCollection<ImageInfo> _importedImages;
// UI updates automatically when collection changes
```

## Building and Running

### Old Build Process
```bash
# Visual Studio with C++ workload required
# Install ATL/MFC
# Open .sln and build
msbuild NikonWatermark.sln /p:Configuration=Release /p:Platform=x64
```

### New Build Process
```bash
# .NET 8 SDK required
cd NikonWatermarkWpf
dotnet restore
dotnet build
dotnet run
```

Much simpler!

## Dependencies

### Old Dependencies
- Windows SDK
- ATL/MFC (included in Visual Studio)
- WTL (header-only, included with ATL)
- GDI+ (part of Windows)

### New Dependencies
- .NET 8 SDK
- MetadataExtractor (via NuGet)
- CommunityToolkit.Mvvm (via NuGet)

Dependencies are managed automatically via NuGet.

## Future Enhancements

The WPF/MVVM architecture makes it easier to add:

1. **Unit Tests**
   - ViewModels can be tested without UI
   - Services are easily mockable

2. **Settings Persistence**
   - Use .NET configuration system
   - JSON-based settings

3. **Batch Processing**
   - Async/await for better responsiveness
   - Progress reporting

4. **Image Preview**
   - Easy to add with WPF's image controls
   - Live preview before processing

5. **Customization**
   - More watermark styles
   - Custom fonts and colors
   - Logo upload

6. **Cross-platform**
   - Port to .NET MAUI for Mac/Linux
   - Share business logic across platforms

## Migration Checklist for Developers

If you're familiar with the old codebase and want to understand the new one:

- [ ] Review `MainViewModel.cs` - equivalent to `MainFrame.cpp` business logic
- [ ] Check `MainWindow.xaml` - UI layout (similar to dialog resources)
- [ ] Examine `Services/ImageProcessorService.cs` - image processing logic
- [ ] Look at `Services/ExifReaderService.cs` - EXIF reading
- [ ] Understand MVVM pattern - Commands instead of message handlers
- [ ] Learn XAML data binding - replaces manual UI updates
- [ ] Familiarize with ObservableCollection - automatic UI synchronization

## Maintenance Notes

### Old Codebase
- **Kept for reference**: The original C++ code remains in `NikonWatermark/` folder
- **No longer actively developed**: Focus is on WPF version
- **Still buildable**: Can be built if needed for legacy purposes

### New Codebase
- **Primary version**: `NikonWatermarkWpf/` is the main project
- **Actively maintained**: All new features go here
- **Recommended for users**: Better UI, easier to maintain

## Support

Both versions are included in the repository:

- **Use WPF version (`NikonWatermarkWpf`)** for new development and general use
- **Use Win32 version (`NikonWatermark`)** only if you have specific C++ requirements

## Conclusion

The migration to WPF/MVVM represents a significant improvement in:
- Code maintainability
- Development productivity
- User experience
- Future extensibility

While the functionality remains the same, the new architecture provides a solid foundation for future enhancements and makes the codebase more accessible to modern .NET developers.
