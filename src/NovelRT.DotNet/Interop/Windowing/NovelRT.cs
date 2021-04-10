// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtWindowingServiceHandle")]
        public static extern IntPtr Nrt_WindowingService_create();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_WindowingService_initialiseWindow([NativeTypeName("NrtWindowingServiceHandle")] IntPtr service, [NativeTypeName("int32_t")] int displayNumber, [NativeTypeName("const char *")] sbyte* windowTitle, NrtWindowMode windowMode, [NativeTypeName("int32_t")] int transparencyEnabled);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_WindowingService_tearDown([NativeTypeName("NrtWindowingServiceHandle")] IntPtr service);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("const char *")]
        public static extern sbyte* Nrt_WindowingService_getWindowTitle([NativeTypeName("NrtWindowingServiceHandle")] IntPtr service);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_WindowingService_setWindowTitle([NativeTypeName("NrtWindowingServiceHandle")] IntPtr service, [NativeTypeName("const char *")] sbyte* value);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_WindowingService_setWindowSize([NativeTypeName("NrtWindowingServiceHandle")] IntPtr service, NrtGeoVector2F value);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_WindowingService_getWindowSize([NativeTypeName("NrtWindowingServiceHandle")] IntPtr service);
    }
}
