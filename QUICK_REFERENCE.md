# Quick Reference Guide

## NikonWatermark - At a Glance

### What It Does
Adds professional watermarks to your photos showing camera settings (aperture, ISO, shutter speed) and manufacturer logo.

### Quick Start
1. **Import** - Click "Import Images" and select photos
2. **Configure** - Choose EXIF fields and position (top/bottom)
3. **Process** - Click "Process Images" and select output folder
4. **Done** - Find watermarked photos in output folder

### Keyboard Shortcuts
| Action | Shortcut |
|--------|----------|
| Exit | Alt+F4 |
| File Menu | Alt+F |

### UI Controls

#### Import Panel (Left)
- Shows selected image files
- Displays filename only

#### Export Panel (Right)
- Shows processing results
- Indicates success/failure per image

#### Settings Panel (Bottom)
**Checkboxes:**
- ☑ Show Aperture (displays f/X.X)
- ☑ Show ISO (displays ISO XXX)
- ☑ Show Shutter Speed (displays 1/XXX or X.Xs)

**Dropdown:**
- Watermark Position: Bottom (default) / Top

**Buttons:**
- Import Images: Select photos to process
- Process Images: Add watermarks and save

### Supported Formats
- **Input**: JPEG (.jpg, .jpeg), PNG (.png), BMP (.bmp)
- **Output**: JPEG (100% quality)

### Supported Cameras
- Nikon (shows "NIKON" logo)
- Canon (shows "Canon" logo)
- Sony (shows "SONY" logo)
- Other manufacturers (shows brand name)

### Watermark Details
- **Position**: Top or bottom with 20px margin
- **Font**: Segoe UI, auto-sized based on image
- **Color**: White text with semi-transparent black shadow
- **Content**: Camera logo + selected EXIF fields

### Example Output
```
[NIKON logo]  f/2.8  ISO 400  1/500
```

### Tips
✓ Select multiple images for batch processing
✓ Test settings on one image first
✓ Keep original photos - output goes to separate folder
✓ Images must have EXIF data to work
✓ Use dedicated output folder for organization

### Common EXIF Values

#### Aperture
- f/1.4, f/1.8, f/2.8, f/4, f/5.6, f/8, f/11, f/16

#### ISO
- ISO 100, 200, 400, 800, 1600, 3200, 6400

#### Shutter Speed
- Fast: 1/4000, 1/2000, 1/1000, 1/500, 1/250
- Medium: 1/125, 1/60, 1/30, 1/15
- Slow: 1/8, 1/4, 1/2, 1s, 2s

### Troubleshooting Quick Fixes

**Problem**: Processing fails
- ✓ Check image has EXIF data
- ✓ Verify output folder is writable

**Problem**: No watermark appears
- ✓ Enable at least one EXIF checkbox
- ✓ Confirm image contains EXIF metadata

**Problem**: Can't import images
- ✓ Check file format (JPEG, PNG, BMP only)
- ✓ Verify files aren't corrupted

### File Locations
```
NikonWatermark/
├── NikonWatermark.exe    # Main application
├── README.md             # Overview and features
├── docs/
│   ├── USER_GUIDE.md     # Detailed user guide
│   └── DEVELOPMENT.md    # Development documentation
└── CHANGELOG.md          # Version history
```

### Requirements
- Windows 10 or Windows 11
- Photos with EXIF metadata
- ~100MB disk space

### Performance
- Processing speed: ~1-2 seconds per image
- Memory usage: Minimal (one image at a time)
- Batch size: No limit

### Quality Settings
- JPEG output quality: 100% (maximum)
- No image resizing or cropping
- Original files remain untouched

### Settings Persistence
⚠ Settings reset when application closes
💡 Future version will save preferences

### Best Practices
1. Always keep backup of original photos
2. Use descriptive output folder names (e.g., "2024-01-Photos-Watermarked")
3. Process test image before batch processing
4. Verify EXIF data in photo viewer before processing
5. Check output quality on first few images

### Getting Help
- Read USER_GUIDE.md for detailed instructions
- Check DEVELOPMENT.md for technical details
- Visit GitHub repository for updates and issues

---
**Version**: 1.0.0  
**Updated**: 2024  
**License**: See LICENSE file
