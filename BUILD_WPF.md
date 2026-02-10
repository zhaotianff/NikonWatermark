# Building NikonWatermark WPF from Source

This guide provides detailed instructions for building the new WPF/MVVM version of NikonWatermark on Windows.

## Prerequisites

### Required Software

1. **.NET 8.0 SDK**
   - Download: https://dotnet.microsoft.com/download/dotnet/8.0
   - Version: 8.0 or later

2. **Visual Studio 2022** (Community, Professional, or Enterprise) - Optional but recommended
   - Download: https://visualstudio.microsoft.com/downloads/
   - Version: 17.0 or later

3. **Visual Studio Workloads** (if using Visual Studio):
   - ✅ .NET desktop development
   - ✅ Windows SDK (comes with .NET desktop development)

### Optional Tools
- Git (for cloning repository)

## Build Environment Setup

### Step 1: Clone Repository

Using Git:
```bash
git clone https://github.com/zhaotianff/NikonWatermark.git
cd NikonWatermark
```

Or download ZIP from GitHub and extract.

### Step 2: Verify .NET SDK Installation

Open a command prompt or PowerShell and run:
```bash
dotnet --version
```

You should see version 8.0.x or later.

## Building the Project

### Method 1: Visual Studio GUI

1. **Open Solution**
   - Launch Visual Studio 2022
   - File → Open → Project/Solution
   - Navigate to `NikonWatermark.sln`
   - Click "Open"

2. **Set Startup Project**
   - Right-click on `NikonWatermarkWpf` project in Solution Explorer
   - Select "Set as Startup Project"

3. **Select Configuration**
   - Configuration: Debug or Release
   - Platform: Any CPU

4. **Restore NuGet Packages**
   - Right-click on solution → Restore NuGet Packages
   - Or Build → Restore NuGet Packages

5. **Build**
   - Build → Build Solution (Ctrl+Shift+B)
   - Wait for compilation to complete
   - Check Output window for any errors

6. **Run**
   - Debug → Start Debugging (F5)
   - Or Debug → Start Without Debugging (Ctrl+F5)

**Output location**:
- Debug: `NikonWatermarkWpf\bin\Debug\net8.0-windows\NikonWatermarkWpf.exe`
- Release: `NikonWatermarkWpf\bin\Release\net8.0-windows\NikonWatermarkWpf.exe`

### Method 2: .NET CLI (Recommended)

1. **Navigate to project directory**
   ```bash
   cd NikonWatermarkWpf
   ```

2. **Restore dependencies**
   ```bash
   dotnet restore
   ```

3. **Build Debug**
   ```bash
   dotnet build -c Debug
   ```

4. **Build Release**
   ```bash
   dotnet build -c Release
   ```

5. **Run the application**
   ```bash
   dotnet run
   ```

### Method 3: MSBuild Command Line

1. **Open Developer Command Prompt**
   - Start Menu → Visual Studio 2022 → Developer Command Prompt for VS 2022

2. **Navigate to solution**
   ```cmd
   cd path\to\NikonWatermark
   ```

3. **Build**
   ```cmd
   msbuild NikonWatermark.sln /p:Configuration=Release
   ```

## Build Configurations

### Debug Configuration
- **Purpose**: Development and debugging
- **Optimizations**: Disabled
- **Debug Info**: Full
- **Output Size**: Larger
- **Performance**: Slower

**Use when**:
- Developing new features
- Debugging issues
- Testing changes

### Release Configuration
- **Purpose**: Production use
- **Optimizations**: Maximum
- **Debug Info**: Minimal
- **Output Size**: Smaller
- **Performance**: Optimal

**Use when**:
- Creating distributable builds
- Performance testing
- End-user releases

## Troubleshooting Build Issues

### Error: "The type or namespace name 'MetadataExtractor' could not be found"

**Solution**: Restore NuGet packages
```bash
dotnet restore
```

Or in Visual Studio:
```
Right-click Solution → Restore NuGet Packages
```

### Error: "NETSDK1100: To build a project targeting Windows"

**Cause**: Building on non-Windows platform or missing Windows SDK

**Solution**: This is a Windows-only application. Build on Windows with Windows SDK installed.

### Error: "The SDK 'Microsoft.NET.Sdk' specified could not be found"

**Cause**: .NET SDK not installed or wrong version

**Solution**: Install .NET 8.0 SDK from https://dotnet.microsoft.com/download/dotnet/8.0

### Warning: "NU1701: Package X was restored using Y instead of the project target framework"

**Solution**: This is usually safe to ignore. The package is compatible but built for an older framework.

## Dependencies

The WPF version uses the following NuGet packages:

- **MetadataExtractor** (2.8.1): For reading EXIF data from images
- **CommunityToolkit.Mvvm** (8.2.2): For MVVM pattern helpers and commands

These are automatically restored during build.

## Creating Distribution Package

### Single-File Executable (Recommended)

Create a self-contained, single-file executable:

```bash
cd NikonWatermarkWpf
dotnet publish -c Release -r win-x64 --self-contained true -p:PublishSingleFile=true
```

Output: `bin\Release\net8.0-windows\win-x64\publish\NikonWatermarkWpf.exe`

This creates a standalone executable with all dependencies included.

### Framework-Dependent Deployment

If users have .NET 8 Runtime installed:

```bash
dotnet publish -c Release -r win-x64 --self-contained false
```

Smaller file size but requires .NET Runtime on target machine.

### Creating ZIP Package

```powershell
# PowerShell script
$version = "2.0.0"
$zipName = "NikonWatermark-WPF-v$version-x64.zip"

# Build and publish
cd NikonWatermarkWpf
dotnet publish -c Release -r win-x64 --self-contained true -p:PublishSingleFile=true

# Create package directory
New-Item -ItemType Directory -Path "dist" -Force

# Copy files
Copy-Item "bin\Release\net8.0-windows\win-x64\publish\NikonWatermarkWpf.exe" -Destination "dist\"
Copy-Item "..\README.md" -Destination "dist\"
Copy-Item "..\LICENSE" -Destination "dist\"

# Create ZIP
Compress-Archive -Path "dist\*" -DestinationPath $zipName -Force

Write-Host "Created: $zipName"
```

## Build Verification

### Verify Successful Build

1. **Check build output**
   ```
   Build succeeded.
       0 Warning(s)
       0 Error(s)
   ```

2. **Check file existence**
   ```bash
   dir bin\Release\net8.0-windows\NikonWatermarkWpf.exe
   ```

3. **Run application**
   ```bash
   cd bin\Release\net8.0-windows
   .\NikonWatermarkWpf.exe
   ```

   Application should launch without errors.

## Performance Testing

```bash
# Build optimized Release version
dotnet build -c Release

# Run performance test
cd bin\Release\net8.0-windows
Measure-Command { .\NikonWatermarkWpf.exe }
```

## Advanced Build Options

### Clean Build
```bash
# .NET CLI
dotnet clean

# MSBuild
msbuild /t:Clean
```

### Verbose Output
```bash
dotnet build -v detailed
```

### AOT Compilation (Advanced)

For faster startup time:
```bash
dotnet publish -c Release -r win-x64 /p:PublishAot=true
```

Note: AOT has some limitations with WPF applications.

## Continuous Integration

### GitHub Actions Example

```yaml
name: Build WPF

on: [push, pull_request]

jobs:
  build:
    runs-on: windows-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Setup .NET
      uses: actions/setup-dotnet@v3
      with:
        dotnet-version: 8.0.x
    
    - name: Restore dependencies
      run: dotnet restore NikonWatermarkWpf/NikonWatermarkWpf.csproj
    
    - name: Build
      run: dotnet build NikonWatermarkWpf/NikonWatermarkWpf.csproj -c Release --no-restore
    
    - name: Publish
      run: dotnet publish NikonWatermarkWpf/NikonWatermarkWpf.csproj -c Release -r win-x64 --self-contained true -p:PublishSingleFile=true
    
    - name: Upload artifact
      uses: actions/upload-artifact@v3
      with:
        name: NikonWatermark-WPF
        path: NikonWatermarkWpf/bin/Release/net8.0-windows/win-x64/publish/
```

## Build Metrics

**Typical build times** (on modern hardware):
- **Clean build**: 10-20 seconds
- **Incremental build**: 2-5 seconds
- **Publish (single-file)**: 15-30 seconds

**Output file sizes**:
- Debug: ~500 KB (plus dependencies)
- Release: ~400 KB (plus dependencies)
- Single-file publish: ~140 MB (all dependencies included)
- Framework-dependent: ~400 KB (requires .NET Runtime)

## Comparing with Legacy Version

The new WPF version offers several advantages over the old Win32/WTL version:

| Feature | WPF/MVVM | Win32/WTL |
|---------|----------|-----------|
| Language | C# | C++ |
| Framework | .NET 8 / WPF | Win32 API / WTL |
| Architecture | MVVM | Event-driven |
| Maintainability | High | Medium |
| Modern UI | Yes | Limited |
| Cross-platform potential | Yes (with .NET MAUI) | Windows only |
| Package management | NuGet | Manual |
| Build complexity | Low | Medium |

## Next Steps

After successful build:
1. Run application and test basic functionality
2. Import sample images to verify UI
3. Process images to verify EXIF reading and watermarking
4. Check output image quality
5. Report any issues on GitHub

## Getting Help

- **Build issues**: Check error messages and troubleshooting section above
- **.NET documentation**: https://docs.microsoft.com/en-us/dotnet/
- **WPF documentation**: https://docs.microsoft.com/en-us/dotnet/desktop/wpf/
- **Project issues**: https://github.com/zhaotianff/NikonWatermark/issues

## License

See LICENSE file for licensing information.
