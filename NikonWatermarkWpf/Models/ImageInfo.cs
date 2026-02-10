namespace NikonWatermarkWpf.Models;

public class ImageInfo
{
    public string FilePath { get; set; } = string.Empty;
    public string FileName { get; set; } = string.Empty;
    public ExifData? ExifData { get; set; }
}
