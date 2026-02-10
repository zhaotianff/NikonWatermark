# NikonWatermark
Nikon Photo Watermark Generator

战歌，启动！

![4ba174094b36acafaaf08f3039d98d1000e99cbc](https://github.com/user-attachments/assets/54dd0440-b771-447d-96d3-3471a49d6121)

## Features

- **Modern WPF UI**: Built with WPF and MVVM pattern for a clean, maintainable architecture
- **Dark UI Theme**: Modern dark fluent-style user interface
- **Dual List View**: Left panel for import images, right panel for export results
- **EXIF Information**: Automatically reads and displays:
  - Aperture (f-stop)
  - ISO sensitivity
  - Shutter speed
- **Camera Logo**: Detects camera manufacturer and displays logo
- **Configurable Display**:
  - Toggle EXIF fields on/off
  - Choose watermark position (Top/Bottom)
- **High Quality**: Preserves original image quality (100% JPEG quality)

## Technology Stack

- **Framework**: .NET 8.0 with WPF
- **Architecture**: MVVM (Model-View-ViewModel)
- **Libraries**:
  - MetadataExtractor for EXIF reading
  - CommunityToolkit.Mvvm for MVVM helpers
- **UI**: XAML with dark theme styling

## Requirements

- Windows 10/11
- .NET 8.0 Runtime (or SDK for building)
- Visual Studio 2022 (for building from source)

## Building

### Option 1: Visual Studio 2022

1. Open `NikonWatermark.sln` in Visual Studio 2022
2. Set `NikonWatermarkWpf` as the startup project
3. Build the solution (Ctrl+Shift+B)
4. Run the application (F5)

### Option 2: .NET CLI

```bash
cd NikonWatermarkWpf
dotnet restore
dotnet build
dotnet run
```

## Usage

1. **Import Images**: Click "Import Images" button to select photos
2. **Configure Settings**:
   - Check/uncheck EXIF fields to display
   - Select watermark position (Top or Bottom)
3. **Process Images**: Click "Process Images" and select output folder
4. View processed images in the export list

## Supported Formats

- Input: JPEG, PNG, BMP
- Output: High-quality JPEG (100% quality)

## Camera Support

The application detects and displays logos for:
- Nikon
- Canon
- Sony
- Other manufacturers (displays brand name)

## Architecture

### MVVM Pattern

The application follows the MVVM (Model-View-ViewModel) pattern:

- **Models**: Data structures (ExifData, WatermarkConfig, ImageInfo)
- **ViewModels**: Business logic and command handlers (MainViewModel)
- **Views**: XAML UI (MainWindow.xaml)
- **Services**: Image processing and EXIF reading services

### Project Structure

```
NikonWatermarkWpf/
├── Models/              # Data models
│   ├── ExifData.cs
│   ├── WatermarkConfig.cs
│   └── ImageInfo.cs
├── ViewModels/          # ViewModels with business logic
│   └── MainViewModel.cs
├── Views/               # XAML views (MainWindow.xaml is in root)
├── Services/            # Business services
│   ├── ExifReaderService.cs
│   └── ImageProcessorService.cs
└── App.xaml            # Application entry point
```

## Legacy Version

The original Win32 WTL C++ version is still available in the `NikonWatermark` folder for reference. The new WPF version (`NikonWatermarkWpf`) is the recommended version going forward.

## Technical Details

- Built with WPF (Windows Presentation Foundation)
- Uses MVVM pattern with CommunityToolkit.Mvvm
- EXIF data reading via MetadataExtractor library
- Image processing using WPF imaging APIs
- Dark theme implemented with custom XAML styles
