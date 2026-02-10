# Changelog

All notable changes to NikonWatermark will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [1.0.0] - 2024

### Added
- Initial release of NikonWatermark application
- Dark theme UI with fluent design style
- Dual list box interface (import/export)
- EXIF metadata reading support
  - Aperture (F-Number)
  - ISO sensitivity
  - Shutter speed (Exposure time)
  - Camera manufacturer
  - Camera model
- Automatic camera manufacturer logo display
  - Nikon support
  - Canon support
  - Sony support
  - Generic manufacturer name fallback
- Watermark positioning (Top/Bottom)
- Configurable EXIF field display
  - Toggle aperture on/off
  - Toggle ISO on/off
  - Toggle shutter speed on/off
- High-quality image output (100% JPEG quality)
- Multi-file import support
- Batch image processing
- GDI+ based image processing
- Support for JPEG, PNG, and BMP input formats
- Professional watermark rendering with shadow effect
- Responsive layout with automatic window resizing
- File and folder selection dialogs

### Technical Details
- Built with Win32 API and WTL (Windows Template Library)
- Uses GDI+ for image processing and rendering
- EXIF reading via GDI+ PropertyItem API
- Dark theme implemented via WM_CTLCOLOR message handlers
- Modern C++ codebase with STL containers
- Visual Studio 2022 project structure

### Documentation
- Comprehensive README with features and build instructions
- User guide with step-by-step instructions
- Development guide for contributors
- Code architecture documentation

[1.0.0]: https://github.com/zhaotianff/NikonWatermark/releases/tag/v1.0.0
