# NikonWatermark
Nikon Photo Watermark Generator

战歌，启动！

![4ba174094b36acafaaf08f3039d98d1000e99cbc](https://github.com/user-attachments/assets/54dd0440-b771-447d-96d3-3471a49d6121)

## Features

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

## Requirements

- Windows 10/11
- Visual Studio 2022 (with C++ Desktop Development workload)
- WTL (Windows Template Library) - included in ATL/MFC workload
- GDI+ (included with Windows)

## Building

1. Open `NikonWatermark.sln` in Visual Studio 2022
2. Ensure WTL is installed (comes with ATL/MFC in Visual Studio)
3. Build the solution (Ctrl+Shift+B)
4. Run the application (F5)

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

## Technical Details

- Built with Win32 API and WTL (Windows Template Library)
- Uses GDI+ for image processing and rendering
- EXIF data reading via GDI+ PropertyItem API
- Dark theme implementation with custom window messages
