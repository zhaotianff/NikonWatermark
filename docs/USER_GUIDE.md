# NikonWatermark User Guide

## Overview

NikonWatermark is a Windows application that adds professional watermarks to your photos by reading and displaying EXIF information directly on the images. The application features a modern dark UI and preserves image quality.

## Getting Started

### System Requirements
- Windows 10 or Windows 11
- At least 100MB of free disk space
- Photo files with EXIF metadata (JPEG, PNG, BMP)

### Installation
1. Download the latest release from the releases page
2. Extract the archive to your desired location
3. Run `NikonWatermark.exe`

## User Interface

The application window is divided into several sections:

### Left Panel - Import Images
- Displays the list of images you've selected to process
- Shows only the filename for clarity

### Right Panel - Export Images
- Shows the list of processed images
- Indicates success or failure for each image

### Settings Panel (Bottom)
Located at the bottom of the window with the following options:

#### EXIF Field Selection
- **Show Aperture**: Displays f-stop value (e.g., f/2.8)
- **Show ISO**: Displays ISO sensitivity (e.g., ISO 400)
- **Show Shutter Speed**: Displays exposure time (e.g., 1/500)

All three checkboxes are enabled by default. Uncheck any to exclude that information from the watermark.

#### Watermark Position
Choose where the watermark appears on your photos:
- **Bottom** (default): Watermark appears at the bottom of the image
- **Top**: Watermark appears at the top of the image

## How to Use

### Step 1: Import Images
1. Click the **"Import Images"** button (or use File → Import Images menu)
2. Select one or multiple image files using the file dialog
3. Supported formats: JPEG (.jpg, .jpeg), PNG (.png), BMP (.bmp)
4. Selected files will appear in the left list box

### Step 2: Configure Settings
1. Check/uncheck EXIF fields based on what you want to display
2. Select watermark position (Top or Bottom)
3. Settings apply to all images in the current batch

### Step 3: Process Images
1. Click the **"Process Images"** button
2. Select an output folder where processed images will be saved
3. The application will process each image and add the watermark
4. Progress is shown in the right list box
5. A success message appears when all images are processed

## Features Explained

### EXIF Reading
The application automatically reads the following EXIF data from your photos:
- **Camera Manufacturer**: Used to display the appropriate logo
- **Camera Model**: Stored but not currently displayed
- **Aperture (F-Number)**: Displayed as f/X.X
- **ISO Speed**: Displayed as ISO XXXX
- **Shutter Speed**: Displayed as 1/XXX or X.Xs

### Camera Logo Support
The application detects the camera manufacturer from EXIF data and displays the brand logo:
- **Nikon**: Shows "NIKON" logo
- **Canon**: Shows "Canon" logo
- **Sony**: Shows "SONY" logo
- **Other brands**: Shows the manufacturer name

Logo is displayed on the left side of the watermark text.

### Image Quality Preservation
- Output images are saved as JPEG with 100% quality setting
- GDI+ encoding ensures minimal quality loss
- Original images are never modified (output to separate folder)

### Watermark Styling
- **Font**: Segoe UI (modern, readable)
- **Size**: Automatically scales based on image size (minimum 12px)
- **Color**: White text with semi-transparent black shadow
- **Position**: 20-pixel margin from edges

## Tips & Best Practices

1. **Batch Processing**: You can select multiple images at once for faster workflow
2. **Organize Output**: Use a dedicated output folder to keep processed images separate
3. **Test Settings**: Process a single image first to verify your settings
4. **EXIF Requirements**: Images must have EXIF data; screenshots or edited images may lack this information
5. **Backup Originals**: Always keep your original photos safe

## Troubleshooting

### "Failed: filename.jpg" in Export List
**Possible causes:**
- Image file is corrupted
- Image lacks EXIF data
- Insufficient disk space in output folder
- File permissions issue

**Solutions:**
- Try opening the image in a photo viewer to verify it's valid
- Check that the image has EXIF metadata
- Ensure you have write permissions to the output folder

### Watermark Text Not Showing
**Possible causes:**
- All EXIF checkboxes are unchecked
- Image has no EXIF data

**Solutions:**
- Enable at least one EXIF field checkbox
- Verify your image contains EXIF metadata using a photo viewer

### Application Won't Start
**Possible causes:**
- Missing Windows components
- Incompatible Windows version

**Solutions:**
- Ensure you're running Windows 10 or later
- Install Visual C++ Redistributables if needed

## Keyboard Shortcuts

- **Alt+F**: Open File menu
- **Alt+F4**: Exit application

## Technical Information

### Supported Image Formats
- **Input**: JPEG, PNG, BMP
- **Output**: JPEG (high quality)

### EXIF Tags Read
- PropertyTagEquipMake (0x010F): Camera manufacturer
- PropertyTagEquipModel (0x0110): Camera model
- PropertyTagExifFNumber (0x829D): Aperture value
- PropertyTagExifISOSpeed (0x8827): ISO sensitivity
- PropertyTagExifExposureTime (0x829A): Shutter speed

### Performance
- Processing speed depends on image size and disk I/O
- Typical processing time: 1-2 seconds per image
- Memory usage: Minimal (loads one image at a time)

## Limitations

1. Only processes images with EXIF metadata
2. Output is always JPEG format
3. Camera logos are text-based, not actual logo images
4. Watermark font and color are fixed
5. Cannot edit watermark text manually

## Future Enhancements

Potential features for future versions:
- Support for RAW image formats
- Custom watermark text
- Adjustable font size and color
- Logo image files for major manufacturers
- PNG output with transparency
- Custom watermark templates
- Batch rename options

## Support

For issues, questions, or feature requests, please visit the project's GitHub repository.

## License

See LICENSE file in the repository for licensing information.
