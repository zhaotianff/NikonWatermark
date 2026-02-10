using System.IO;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using NikonWatermarkWpf.Models;

namespace NikonWatermarkWpf.Services;

public class ImageProcessorService
{
    private readonly ExifReaderService _exifReader;

    public ImageProcessorService()
    {
        _exifReader = new ExifReaderService();
    }

    public bool ProcessImage(string inputPath, string outputPath, WatermarkConfig config)
    {
        try
        {
            // Read EXIF data
            var exifData = _exifReader.ReadExifData(inputPath);

            // Load the image
            BitmapImage originalImage = new BitmapImage();
            originalImage.BeginInit();
            originalImage.UriSource = new Uri(inputPath);
            originalImage.CacheOption = BitmapCacheOption.OnLoad;
            originalImage.EndInit();

            // Create a DrawingVisual to render the watermark
            var drawingVisual = new DrawingVisual();
            using (var drawingContext = drawingVisual.RenderOpen())
            {
                // Draw original image
                drawingContext.DrawImage(originalImage, new Rect(0, 0, originalImage.PixelWidth, originalImage.PixelHeight));

                // Draw watermark
                DrawWatermark(drawingContext, exifData, config, originalImage.PixelWidth, originalImage.PixelHeight);
            }

            // Render to bitmap
            var renderTargetBitmap = new RenderTargetBitmap(
                originalImage.PixelWidth,
                originalImage.PixelHeight,
                96, 96,
                PixelFormats.Pbgra32);
            renderTargetBitmap.Render(drawingVisual);

            // Save to file
            SaveImage(renderTargetBitmap, outputPath);

            return true;
        }
        catch (Exception ex)
        {
            System.Diagnostics.Debug.WriteLine($"Error processing image: {ex.Message}");
            return false;
        }
    }

    private void DrawWatermark(DrawingContext dc, ExifData exifData, WatermarkConfig config, int imageWidth, int imageHeight)
    {
        // Build watermark text
        var watermarkText = BuildWatermarkText(exifData, config);
        if (string.IsNullOrWhiteSpace(watermarkText))
            return;

        // Watermark settings
        var fontSize = imageHeight * 0.025; // 2.5% of image height
        var padding = imageHeight * 0.015;
        var logoSize = fontSize * 1.8;

        var typeface = new Typeface(new FontFamily("Segoe UI"), FontStyles.Normal, FontWeights.Normal, FontStretches.Normal);
        var formattedText = new FormattedText(
            watermarkText,
            System.Globalization.CultureInfo.CurrentCulture,
            FlowDirection.LeftToRight,
            typeface,
            fontSize,
            Brushes.White,
            VisualTreeHelper.GetDpi(Application.Current.MainWindow).PixelsPerDip);

        // Calculate position
        double y = config.Position == WatermarkPosition.Bottom
            ? imageHeight - formattedText.Height - padding * 2
            : padding;

        // Draw semi-transparent background
        var bgRect = new Rect(
            padding,
            y - padding,
            formattedText.Width + logoSize + padding * 3,
            formattedText.Height + padding * 2);
        dc.DrawRectangle(new SolidColorBrush(Color.FromArgb(180, 0, 0, 0)), null, bgRect);

        // Draw logo (simplified - just draw manufacturer text for now)
        var logoText = new FormattedText(
            GetManufacturerLogo(exifData.Manufacturer),
            System.Globalization.CultureInfo.CurrentCulture,
            FlowDirection.LeftToRight,
            typeface,
            logoSize,
            Brushes.White,
            VisualTreeHelper.GetDpi(Application.Current.MainWindow).PixelsPerDip);
        dc.DrawText(logoText, new Point(padding * 2, y));

        // Draw watermark text
        dc.DrawText(formattedText, new Point(padding * 3 + logoSize, y));
    }

    private string BuildWatermarkText(ExifData exifData, WatermarkConfig config)
    {
        var parts = new List<string>();

        if (config.ShowAperture && !string.IsNullOrWhiteSpace(exifData.Aperture))
        {
            parts.Add(exifData.Aperture);
        }

        if (config.ShowIso && !string.IsNullOrWhiteSpace(exifData.Iso))
        {
            parts.Add($"ISO {exifData.Iso}");
        }

        if (config.ShowShutterSpeed && !string.IsNullOrWhiteSpace(exifData.ShutterSpeed))
        {
            parts.Add(exifData.ShutterSpeed);
        }

        return string.Join("  ", parts);
    }

    private string GetManufacturerLogo(string manufacturer)
    {
        if (string.IsNullOrWhiteSpace(manufacturer))
            return "📷";

        var mfr = manufacturer.ToLowerInvariant();
        if (mfr.Contains("nikon"))
            return "NIKON";
        if (mfr.Contains("canon"))
            return "CANON";
        if (mfr.Contains("sony"))
            return "SONY";

        return manufacturer.ToUpperInvariant();
    }

    private void SaveImage(BitmapSource bitmap, string outputPath)
    {
        var encoder = new JpegBitmapEncoder();
        encoder.QualityLevel = 100;
        encoder.Frames.Add(BitmapFrame.Create(bitmap));

        using var fileStream = new FileStream(outputPath, FileMode.Create);
        encoder.Save(fileStream);
    }
}
