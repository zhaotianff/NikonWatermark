using MetadataExtractor;
using MetadataExtractor.Formats.Exif;
using NikonWatermarkWpf.Models;

namespace NikonWatermarkWpf.Services;

public class ExifReaderService
{
    public ExifData ReadExifData(string filePath)
    {
        var exifData = new ExifData();

        try
        {
            var directories = ImageMetadataReader.ReadMetadata(filePath);

            // Get manufacturer and model
            var ifd0Directory = directories.OfType<ExifIfd0Directory>().FirstOrDefault();
            if (ifd0Directory != null)
            {
                exifData.Manufacturer = ifd0Directory.GetDescription(ExifDirectoryBase.TagMake) ?? string.Empty;
                exifData.Model = ifd0Directory.GetDescription(ExifDirectoryBase.TagModel) ?? string.Empty;
            }

            // Get EXIF data
            var exifSubIfdDirectory = directories.OfType<ExifSubIfdDirectory>().FirstOrDefault();
            if (exifSubIfdDirectory != null)
            {
                // Aperture (F-stop)
                var aperture = exifSubIfdDirectory.GetDescription(ExifDirectoryBase.TagFNumber);
                if (!string.IsNullOrEmpty(aperture))
                {
                    exifData.Aperture = aperture;
                }

                // ISO
                var iso = exifSubIfdDirectory.GetDescription(ExifDirectoryBase.TagIsoEquivalent);
                if (!string.IsNullOrEmpty(iso))
                {
                    exifData.Iso = iso;
                }

                // Shutter Speed (Exposure Time)
                var shutterSpeed = exifSubIfdDirectory.GetDescription(ExifDirectoryBase.TagExposureTime);
                if (!string.IsNullOrEmpty(shutterSpeed))
                {
                    exifData.ShutterSpeed = shutterSpeed;
                }
            }
        }
        catch (Exception ex)
        {
            System.Diagnostics.Debug.WriteLine($"Error reading EXIF data: {ex.Message}");
        }

        return exifData;
    }
}
