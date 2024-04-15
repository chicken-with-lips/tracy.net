using System.Runtime.InteropServices;

namespace Tracy;

public static class TracyClient
{
    [DllImport("Tracy.Native", EntryPoint = "tracy_FrameMark")]
    public static extern void FrameMark();

    [DllImport("Tracy.Native", EntryPoint = "tracy_ZoneScoped")]
    public static extern void ZoneScoped();

    public static void ZoneBegin()
    {
        _ZoneBegin();
    }

    public static void ZoneBegin(string name)
    {
        _ZoneBegin();
        _ZoneName(name, name.Length);
    }

    public static void Zone(string name, Action action)
    {
        _ZoneBegin();
        _ZoneName(name, name.Length);

        action();

        ZoneEnd();
    }

    public static void Zone<T>(string name, Action<T> action, T actionArg)
    {
        _ZoneBegin();
        _ZoneName(name, name.Length);

        action(actionArg);

        ZoneEnd();
    }

    [DllImport("Tracy.Native", EntryPoint = "tracy_ZoneBegin")]
    private static extern void _ZoneBegin();

    [DllImport("Tracy.Native", EntryPoint = "tracy_ZoneEnd")]
    public static extern void ZoneEnd();

    [DllImport("Tracy.Native", EntryPoint = "tracy_ZoneName")]
    private static extern void _ZoneName(string name, int length);
}
