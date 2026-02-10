namespace NikonWatermarkWpf.Models;

public enum WatermarkPosition
{
    Top,
    Bottom
}

public class WatermarkConfig
{
    public bool ShowAperture { get; set; } = true;
    public bool ShowIso { get; set; } = true;
    public bool ShowShutterSpeed { get; set; } = true;
    public WatermarkPosition Position { get; set; } = WatermarkPosition.Bottom;
}
