// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("const char *")]
        public static extern sbyte* Nrt_getExecutablePath();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("const char *")]
        public static extern sbyte* Nrt_getExecutableDirPath();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("const char *")]
        public static extern sbyte* Nrt_appendFilePath([NativeTypeName("int32_t")] int numberOfArgs, [NativeTypeName("const char *const *")] sbyte** args);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("const char *")]
        public static extern sbyte* Nrt_appendText([NativeTypeName("int32_t")] int numberOfArgs, [NativeTypeName("const char *const *")] sbyte** args);
    }
}
