# Changelog

All notable changes to NikonWatermark will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [2.0.0] - 2024

### Added - WPF/MVVM Version
- **Complete rewrite** using WPF and MVVM architecture pattern
- New `NikonWatermarkWpf` project with modern .NET 8 framework
- MVVM architecture with clear separation of concerns
  - Models: ExifData, WatermarkConfig, ImageInfo
  - ViewModels: MainViewModel with INotifyPropertyChanged
  - Views: XAML-based declarative UI
  - Services: ImageProcessorService, ExifReaderService
- Enhanced UI with XAML styling
  - Modern dark theme with rounded corners
  - Better visual hierarchy
  - Smooth hover and press effects
  - Professional button and control styling
- Improved EXIF reading using MetadataExtractor library
  - More reliable EXIF data extraction
  - Better error handling
  - Support for more camera types
- Command-based user interactions (ICommand)
- Data binding for automatic UI updates
- ObservableCollection for list management
- NuGet package management for dependencies
  - MetadataExtractor for EXIF data
  - CommunityToolkit.Mvvm for MVVM helpers

### Technical Improvements
- Migration from C++ to C#
- Modern async/await ready architecture
- Better testability with separated concerns
- Cleaner codebase with less boilerplate
- Type-safe data binding
- Automatic UI synchronization

### Documentation
- New BUILD_WPF.md with comprehensive build instructions
- MIGRATION_GUIDE.md explaining Win32 to WPF transition
- Updated README.md with WPF version information
- Architecture documentation in migration guide
- Code comparison examples

### Maintained
- Original Win32/WTL C++ version kept in `NikonWatermark/` folder
- All original features preserved in WPF version
- Feature parity between old and new versions
- Both versions can coexist in the same solution

### Changed
- Primary development focus moved to WPF version
- Recommended version for new users is WPF
- Solution file updated to include both projects

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

[2.0.0]: https://github.com/zhaotianff/NikonWatermark/releases/tag/v2.0.0
[1.0.0]: https://github.com/zhaotianff/NikonWatermark/releases/tag/v1.0.0
