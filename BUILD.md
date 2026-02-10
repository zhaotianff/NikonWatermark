# Building NikonWatermark from Source

This guide provides detailed instructions for building NikonWatermark on Windows.

## Prerequisites

### Required Software

1. **Visual Studio 2022** (Community, Professional, or Enterprise)
   - Download: https://visualstudio.microsoft.com/downloads/
   - Version: 17.0 or later

2. **Visual Studio Workloads** (during installation, select):
   - ✅ Desktop development with C++
   - ✅ Windows 10 SDK (10.0.19041.0 or later)

3. **ATL/WTL Support** (included in Desktop C++ workload):
   - ✅ C++ ATL for latest build tools
   - ✅ C++ MFC for latest build tools

### Optional Tools
- Git (for cloning repository)
- CMake (not required for this project)

## Build Environment Setup

### Step 1: Clone Repository

Using Git:
```bash
git clone https://github.com/zhaotianff/NikonWatermark.git
cd NikonWatermark
```

Or download ZIP from GitHub and extract.

### Step 2: Verify Prerequisites

1. Open Visual Studio Installer
2. Click "Modify" on your Visual Studio 2022 installation
3. Verify "Desktop development with C++" is checked
4. Under "Individual components", search and verify:
   - ✅ C++ ATL for latest v143 build tools (x86 & x64)
   - ✅ C++ MFC for latest v143 build tools (x86 & x64)
   - ✅ Windows 10 SDK (any version 10.0.19041.0 or later)

### Step 3: WTL Installation Check

WTL (Windows Template Library) is included with Visual Studio's ATL/MFC installation.

**Verify WTL path** (should exist):
```
C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\[version]\atlmfc\include\
```

Files to look for:
- atlapp.h
- atlframe.h
- atlctrls.h
- atldlgs.h

## Building the Project

### Method 1: Visual Studio GUI

1. **Open Solution**
   - Launch Visual Studio 2022
   - File → Open → Project/Solution
   - Navigate to `NikonWatermark.sln`
   - Click "Open"

2. **Select Configuration**
   - Configuration: Debug or Release
   - Platform: x64 (recommended)

3. **Build**
   - Build → Build Solution (Ctrl+Shift+B)
   - Wait for compilation to complete
   - Check Output window for any errors

4. **Run**
   - Debug → Start Debugging (F5)
   - Or Debug → Start Without Debugging (Ctrl+F5)

**Output location**:
- Debug: `x64\Debug\NikonWatermark.exe`
- Release: `x64\Release\NikonWatermark.exe`

### Method 2: MSBuild Command Line

1. **Open Developer Command Prompt**
   - Start Menu → Visual Studio 2022 → Developer Command Prompt for VS 2022

2. **Navigate to project**
   ```cmd
   cd path\to\NikonWatermark
   ```

3. **Build Debug**
   ```cmd
   msbuild NikonWatermark.sln /p:Configuration=Debug /p:Platform=x64
   ```

4. **Build Release**
   ```cmd
   msbuild NikonWatermark.sln /p:Configuration=Release /p:Platform=x64
   ```

5. **Rebuild (clean + build)**
   ```cmd
   msbuild NikonWatermark.sln /t:Rebuild /p:Configuration=Release /p:Platform=x64
   ```

### Method 3: Developer PowerShell

1. **Open Developer PowerShell**
   - Start Menu → Visual Studio 2022 → Developer PowerShell for VS 2022

2. **Navigate and build**
   ```powershell
   cd path\to\NikonWatermark
   msbuild NikonWatermark.sln /p:Configuration=Release /p:Platform=x64
   ```

## Build Configurations

### Debug Configuration
- **Purpose**: Development and debugging
- **Optimizations**: Disabled
- **Debug Info**: Full
- **Runtime Checks**: Enabled
- **Output Size**: Larger (~500 KB)
- **Performance**: Slower

**Use when**:
- Developing new features
- Debugging issues
- Testing changes

### Release Configuration
- **Purpose**: Production use
- **Optimizations**: Maximum speed
- **Debug Info**: Minimal (PDB file)
- **Runtime Checks**: Disabled
- **Output Size**: Smaller (~200 KB)
- **Performance**: Optimal

**Use when**:
- Creating distributable builds
- Performance testing
- End-user releases

## Troubleshooting Build Issues

### Error: "Cannot open include file: 'atlbase.h'"

**Solution**: Install ATL/MFC components
```
1. Open Visual Studio Installer
2. Modify Visual Studio 2022
3. Individual Components tab
4. Search "ATL"
5. Check "C++ ATL for latest v143 build tools"
6. Install
```

### Error: "Cannot open include file: 'gdiplus.h'"

**Solution**: Install Windows SDK
```
1. Open Visual Studio Installer
2. Modify Visual Studio 2022
3. Individual Components tab
4. Search "Windows 10 SDK"
5. Check latest SDK version (e.g., 10.0.22621.0)
6. Install
```

### Error: "LNK1104: cannot open file 'gdiplus.lib'"

**Cause**: Linker cannot find GDI+ library

**Solution**: Verify project settings
```
1. Right-click project → Properties
2. Linker → Input
3. Additional Dependencies should include: gdiplus.lib
4. If missing, add: gdiplus.lib;%(AdditionalDependencies)
```

### Error: MSB8036: Windows SDK version not found

**Solution**: Update SDK version in project
```
1. Right-click project → Properties
2. General → Windows SDK Version
3. Select an installed SDK version
4. Click OK
5. Rebuild
```

Or edit `.vcxproj` file:
```xml
<WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>
```
Change to specific version like `10.0.22621.0`

### Error: "Unresolved external symbol" for WTL classes

**Solution**: Check include paths
```
1. Right-click project → Properties
2. C/C++ → General → Additional Include Directories
3. Should include: $(ProjectDir);%(AdditionalIncludeDirectories)
4. Apply and rebuild
```

### Warning: C4996 (deprecated function)

**Solution**: Suppress specific warnings (if intentional)
```
1. Right-click project → Properties
2. C/C++ → Advanced → Disable Specific Warnings
3. Add: 4996
```

Or use:
```cpp
#pragma warning(disable: 4996)
```

## Build Verification

### Verify Successful Build

1. **Check Output Window**
   ```
   Build: 1 succeeded, 0 failed, 0 up-to-date, 0 skipped
   ```

2. **Check File Existence**
   ```
   x64\Release\NikonWatermark.exe (exists)
   x64\Release\NikonWatermark.pdb (exists)
   ```

3. **Run Application**
   ```cmd
   cd x64\Release
   NikonWatermark.exe
   ```
   Application should launch without errors.

### Performance Test Build

```cmd
:: Build Release
msbuild /t:Rebuild /p:Configuration=Release /p:Platform=x64

:: Check file size (should be ~200-300 KB)
dir x64\Release\NikonWatermark.exe

:: Run and test performance
x64\Release\NikonWatermark.exe
```

## Advanced Build Options

### Clean Build
```cmd
:: MSBuild
msbuild /t:Clean /p:Configuration=Release /p:Platform=x64

:: Visual Studio
Build → Clean Solution
```

### Parallel Build
```cmd
:: Use multiple cores (faster)
msbuild /m /p:Configuration=Release /p:Platform=x64
```

### Verbose Output
```cmd
:: Detailed build log
msbuild /v:detailed /p:Configuration=Release /p:Platform=x64
```

### Build to Custom Directory
```cmd
:: Override output directory
msbuild /p:OutDir=C:\Build\Output\ /p:Configuration=Release /p:Platform=x64
```

## Code Signing (Optional)

For distributing signed executables:

```cmd
:: Using signtool (in Windows SDK)
signtool sign /f MyCert.pfx /p password /t http://timestamp.digicert.com x64\Release\NikonWatermark.exe
```

## Creating Distribution Package

### Standalone Executable

Release build is standalone - just distribute `NikonWatermark.exe`

**No additional DLLs needed** because:
- GDI+ is part of Windows
- Statically linked to C++ runtime
- No external dependencies

### Creating ZIP Package

```powershell
# PowerShell script
$version = "1.0.0"
$zipName = "NikonWatermark-v$version-x64.zip"

# Create package directory
New-Item -ItemType Directory -Path "dist" -Force

# Copy files
Copy-Item "x64\Release\NikonWatermark.exe" -Destination "dist\"
Copy-Item "README.md" -Destination "dist\"
Copy-Item "LICENSE" -Destination "dist\"
Copy-Item "QUICK_REFERENCE.md" -Destination "dist\"
Copy-Item "docs" -Destination "dist\" -Recurse

# Create ZIP
Compress-Archive -Path "dist\*" -DestinationPath $zipName -Force

Write-Host "Created: $zipName"
```

### Creating Installer (Advanced)

Use tools like:
- Inno Setup
- WiX Toolset
- NSIS

Example Inno Setup script:
```iss
[Setup]
AppName=NikonWatermark
AppVersion=1.0.0
DefaultDirName={pf}\NikonWatermark
DefaultGroupName=NikonWatermark
OutputDir=installer
OutputBaseFilename=NikonWatermark-Setup-1.0.0

[Files]
Source: "x64\Release\NikonWatermark.exe"; DestDir: "{app}"
Source: "README.md"; DestDir: "{app}"
Source: "LICENSE"; DestDir: "{app}"

[Icons]
Name: "{group}\NikonWatermark"; Filename: "{app}\NikonWatermark.exe"
```

## Continuous Integration

### GitHub Actions Example

```yaml
name: Build

on: [push, pull_request]

jobs:
  build:
    runs-on: windows-latest
    
    steps:
    - uses: actions/checkout@v2
    
    - name: Setup MSBuild
      uses: microsoft/setup-msbuild@v1
    
    - name: Build
      run: msbuild NikonWatermark.sln /p:Configuration=Release /p:Platform=x64
    
    - name: Upload artifact
      uses: actions/upload-artifact@v2
      with:
        name: NikonWatermark
        path: x64/Release/NikonWatermark.exe
```

## Build Metrics

**Typical build times** (on modern hardware):
- **Clean build**: 10-15 seconds
- **Incremental build**: 2-5 seconds
- **Rebuild**: 12-18 seconds

**Output file sizes**:
- Debug: ~500 KB
- Release: ~200-300 KB
- PDB (debug symbols): ~1-2 MB

## Next Steps

After successful build:
1. Run application and test basic functionality
2. Process a sample image to verify EXIF reading
3. Check output image quality
4. Review documentation in `docs/` folder
5. Report any issues on GitHub

## Getting Help

- **Build issues**: Check error messages and troubleshooting section above
- **Visual Studio help**: https://docs.microsoft.com/en-us/visualstudio/
- **MSBuild reference**: https://docs.microsoft.com/en-us/visualstudio/msbuild/
- **WTL forums**: http://wtl.sourceforge.net/

## License

See LICENSE file for licensing information.
