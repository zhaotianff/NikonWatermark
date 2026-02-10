using System.Collections.ObjectModel;
using System.IO;
using System.Windows;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.Win32;
using NikonWatermarkWpf.Models;
using NikonWatermarkWpf.Services;

namespace NikonWatermarkWpf.ViewModels;

public partial class MainViewModel : ObservableObject
{
    private readonly ImageProcessorService _imageProcessor;

    [ObservableProperty]
    private ObservableCollection<ImageInfo> _importedImages = new();

    [ObservableProperty]
    private ObservableCollection<string> _exportedImages = new();

    [ObservableProperty]
    private bool _showAperture = true;

    [ObservableProperty]
    private bool _showIso = true;

    [ObservableProperty]
    private bool _showShutterSpeed = true;

    [ObservableProperty]
    private int _selectedPositionIndex = 1; // Bottom

    public ObservableCollection<string> PositionOptions { get; } = new()
    {
        "Top",
        "Bottom"
    };

    public MainViewModel()
    {
        _imageProcessor = new ImageProcessorService();
    }

    [RelayCommand]
    private void ImportImages()
    {
        var openFileDialog = new OpenFileDialog
        {
            Multiselect = true,
            Filter = "Image Files|*.jpg;*.jpeg;*.png;*.bmp|All Files|*.*",
            Title = "Select Images to Import"
        };

        if (openFileDialog.ShowDialog() == true)
        {
            foreach (var fileName in openFileDialog.FileNames)
            {
                var imageInfo = new ImageInfo
                {
                    FilePath = fileName,
                    FileName = Path.GetFileName(fileName)
                };
                ImportedImages.Add(imageInfo);
            }
        }
    }

    [RelayCommand]
    private void ProcessImages()
    {
        if (ImportedImages.Count == 0)
        {
            MessageBox.Show("Please import images first.", "No Images", MessageBoxButton.OK, MessageBoxImage.Information);
            return;
        }

        var folderDialog = new OpenFolderDialog
        {
            Title = "Select Output Folder"
        };

        if (folderDialog.ShowDialog() == true)
        {
            var outputFolder = folderDialog.FolderName;
            var config = new WatermarkConfig
            {
                ShowAperture = ShowAperture,
                ShowIso = ShowIso,
                ShowShutterSpeed = ShowShutterSpeed,
                Position = SelectedPositionIndex == 0 ? WatermarkPosition.Top : WatermarkPosition.Bottom
            };

            ExportedImages.Clear();
            int successCount = 0;
            int failCount = 0;

            foreach (var imageInfo in ImportedImages)
            {
                try
                {
                    var fileName = Path.GetFileNameWithoutExtension(imageInfo.FilePath);
                    var extension = Path.GetExtension(imageInfo.FilePath);
                    var outputPath = Path.Combine(outputFolder, $"{fileName}_watermarked.jpg");

                    if (_imageProcessor.ProcessImage(imageInfo.FilePath, outputPath, config))
                    {
                        ExportedImages.Add(Path.GetFileName(outputPath));
                        successCount++;
                    }
                    else
                    {
                        failCount++;
                    }
                }
                catch (Exception ex)
                {
                    System.Diagnostics.Debug.WriteLine($"Error processing {imageInfo.FileName}: {ex.Message}");
                    failCount++;
                }
            }

            MessageBox.Show(
                $"Processing complete!\n\nSuccessful: {successCount}\nFailed: {failCount}",
                "Processing Complete",
                MessageBoxButton.OK,
                MessageBoxImage.Information);
        }
    }
}
