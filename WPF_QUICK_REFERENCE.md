# WPF Quick Reference

Quick reference guide for the NikonWatermark WPF/MVVM application.

## Project Structure

```
NikonWatermarkWpf/
├── Models/                          # Data models (POCOs)
│   ├── ExifData.cs                 # EXIF metadata structure
│   ├── WatermarkConfig.cs          # Watermark settings
│   └── ImageInfo.cs                # Image file information
├── ViewModels/                      # Business logic & state
│   └── MainViewModel.cs            # Main window view model
├── Services/                        # Business services
│   ├── ExifReaderService.cs       # EXIF data extraction
│   └── ImageProcessorService.cs   # Image processing & watermarking
├── App.xaml                         # Application entry point
├── App.xaml.cs                      # Application code-behind
├── MainWindow.xaml                  # Main window UI (XAML)
├── MainWindow.xaml.cs              # Main window code-behind
└── NikonWatermarkWpf.csproj        # Project file
```

## Key Classes

### MainViewModel
**Location:** `ViewModels/MainViewModel.cs`

**Responsibilities:**
- Manages application state
- Handles user commands (Import, Process)
- Coordinates between UI and services
- Provides data to the view via binding

**Key Properties:**
- `ImportedImages`: Collection of imported images
- `ExportedImages`: Collection of exported file names
- `ShowAperture`, `ShowIso`, `ShowShutterSpeed`: EXIF field toggles
- `SelectedPositionIndex`: Watermark position

**Key Commands:**
- `ImportImagesCommand`: Opens file dialog and adds images
- `ProcessImagesCommand`: Processes all images with watermarks

### ExifReaderService
**Location:** `Services/ExifReaderService.cs`

**Responsibilities:**
- Reads EXIF metadata from images
- Uses MetadataExtractor library
- Returns structured ExifData

**Key Method:**
```csharp
ExifData ReadExifData(string filePath)
```

### ImageProcessorService
**Location:** `Services/ImageProcessorService.cs`

**Responsibilities:**
- Processes images with watermarks
- Uses WPF imaging APIs
- Renders text and graphics on images
- Saves output as high-quality JPEG

**Key Method:**
```csharp
bool ProcessImage(string inputPath, string outputPath, WatermarkConfig config)
```

## XAML UI Structure

### MainWindow.xaml

```xml
Window (Dark theme #1E1E1E)
└── Grid (3 rows)
    ├── Title Row
    │   └── TextBlock "Nikon Photo Watermark Generator"
    ├── Main Content Row
    │   └── Grid (3 columns)
    │       ├── Left Panel (Import)
    │       │   ├── Label "Import Images"
    │       │   ├── ListBox (bound to ImportedImages)
    │       │   └── Button "Import Images" (ImportImagesCommand)
    │       ├── Middle Panel (Settings)
    │       │   ├── CheckBox "Aperture" (ShowAperture)
    │       │   ├── CheckBox "ISO" (ShowIso)
    │       │   ├── CheckBox "Shutter Speed" (ShowShutterSpeed)
    │       │   └── ComboBox (Position selection)
    │       └── Right Panel (Export)
    │           ├── Label "Export Results"
    │           ├── ListBox (bound to ExportedImages)
    │           └── Button "Process Images" (ProcessImagesCommand)
    └── Status Bar Row
        └── Border "战歌，启动！Ready to process images"
```

## Data Flow

### Import Images Flow
```
User clicks "Import Images" button
    ↓
ImportImagesCommand executes
    ↓
OpenFileDialog shows
    ↓
User selects files
    ↓
Files added to ImportedImages collection
    ↓
UI updates automatically via data binding
```

### Process Images Flow
```
User clicks "Process Images" button
    ↓
ProcessImagesCommand executes
    ↓
OpenFolderDialog shows for output location
    ↓
For each imported image:
    ├── ImageProcessorService.ProcessImage()
    │   ├── ExifReaderService.ReadExifData()
    │   ├── Load image
    │   ├── Render watermark with EXIF data
    │   └── Save to output folder
    └── Add to ExportedImages collection
    ↓
UI updates automatically
    ↓
MessageBox shows completion summary
```

## Data Binding

### ViewModel to View Binding

**ViewModel Property:**
```csharp
[ObservableProperty]
private ObservableCollection<ImageInfo> _importedImages = new();
```

**XAML Binding:**
```xml
<ListBox ItemsSource="{Binding ImportedImages}" 
         DisplayMemberPath="FileName"/>
```

### Command Binding

**ViewModel Command:**
```csharp
[RelayCommand]
private void ImportImages() { ... }
```

**XAML Binding:**
```xml
<Button Command="{Binding ImportImagesCommand}" 
        Content="Import Images"/>
```

## NuGet Dependencies

### MetadataExtractor (2.8.1)
- Purpose: Read EXIF metadata from images
- Used in: `ExifReaderService`
- Supports: JPEG, PNG, BMP, and more

### CommunityToolkit.Mvvm (8.2.2)
- Purpose: MVVM helpers and base classes
- Features:
  - `[ObservableProperty]`: Auto-generates property change notifications
  - `[RelayCommand]`: Auto-generates ICommand implementations
  - Source generators for reduced boilerplate

## Common Tasks

### Adding a New EXIF Field

1. **Update ExifData model:**
```csharp
public class ExifData
{
    // Existing fields...
    public string FocalLength { get; set; } = string.Empty;
}
```

2. **Update ExifReaderService:**
```csharp
var focalLength = exifSubIfdDirectory.GetDescription(ExifDirectoryBase.TagFocalLength);
if (!string.IsNullOrEmpty(focalLength))
{
    exifData.FocalLength = focalLength;
}
```

3. **Update WatermarkConfig:**
```csharp
public class WatermarkConfig
{
    // Existing fields...
    public bool ShowFocalLength { get; set; } = true;
}
```

4. **Update MainViewModel:**
```csharp
[ObservableProperty]
private bool _showFocalLength = true;

// In ProcessImages:
ShowFocalLength = ShowFocalLength,
```

5. **Update UI (MainWindow.xaml):**
```xml
<CheckBox Content="Focal Length" 
          IsChecked="{Binding ShowFocalLength}"/>
```

6. **Update watermark rendering:**
```csharp
if (config.ShowFocalLength && !string.IsNullOrWhiteSpace(exifData.FocalLength))
{
    parts.Add(exifData.FocalLength);
}
```

### Changing the Dark Theme

**Edit MainWindow.xaml Resources:**
```xml
<Window.Resources>
    <!-- Change background color -->
    <SolidColorBrush x:Key="BackgroundBrush" Color="#1E1E1E"/>
    
    <!-- Change accent color -->
    <SolidColorBrush x:Key="AccentBrush" Color="#007ACC"/>
    
    <!-- Apply to window -->
    <Style TargetType="Window">
        <Setter Property="Background" Value="{StaticResource BackgroundBrush}"/>
    </Style>
</Window.Resources>
```

### Adding New Commands

1. **In ViewModel:**
```csharp
[RelayCommand]
private void ClearImages()
{
    ImportedImages.Clear();
    ExportedImages.Clear();
}
```

2. **In XAML:**
```xml
<Button Content="Clear All" 
        Command="{Binding ClearImagesCommand}"/>
```

## Build Commands

### Development
```bash
cd NikonWatermarkWpf
dotnet restore
dotnet build
dotnet run
```

### Release Build
```bash
dotnet build -c Release
```

### Publish (Single-File)
```bash
dotnet publish -c Release -r win-x64 --self-contained true -p:PublishSingleFile=true
```

## Debugging

### Visual Studio
1. Set `NikonWatermarkWpf` as startup project
2. Press F5 to start debugging
3. Breakpoints work in C# and XAML

### VS Code with C# Extension
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": ".NET Core Launch (WPF)",
            "type": "coreclr",
            "request": "launch",
            "preLaunchTask": "build",
            "program": "${workspaceFolder}/NikonWatermarkWpf/bin/Debug/net8.0-windows/NikonWatermarkWpf.dll",
            "cwd": "${workspaceFolder}/NikonWatermarkWpf",
            "console": "internalConsole"
        }
    ]
}
```

## Testing

### Manual Testing Checklist
- [ ] Import single image
- [ ] Import multiple images
- [ ] Toggle EXIF fields
- [ ] Change watermark position
- [ ] Process images
- [ ] Verify output quality
- [ ] Check EXIF data accuracy
- [ ] Test with different image formats (JPEG, PNG, BMP)
- [ ] Test with images missing EXIF data

### Unit Testing (Future)
```csharp
[TestClass]
public class ExifReaderServiceTests
{
    [TestMethod]
    public void ReadExifData_ValidImage_ReturnsData()
    {
        var service = new ExifReaderService();
        var result = service.ReadExifData("test-image.jpg");
        Assert.IsNotNull(result);
    }
}
```

## Performance Tips

1. **Large Image Sets**: Process in batches with async/await
2. **Memory**: Dispose images properly (WPF handles this)
3. **UI Responsiveness**: Keep commands quick, move heavy work to background

## Troubleshooting

### Build Errors
```bash
# Clear build artifacts
dotnet clean

# Restore packages
dotnet restore

# Rebuild
dotnet build
```

### Runtime Errors
- Check Output window for exceptions
- Verify file paths exist
- Ensure images are valid formats
- Check EXIF data exists in images

## Resources

- [WPF Documentation](https://docs.microsoft.com/en-us/dotnet/desktop/wpf/)
- [MVVM Pattern](https://docs.microsoft.com/en-us/dotnet/architecture/maui/mvvm)
- [CommunityToolkit.Mvvm Docs](https://learn.microsoft.com/en-us/dotnet/communitytoolkit/mvvm/)
- [MetadataExtractor](https://github.com/drewnoakes/metadata-extractor-dotnet)
