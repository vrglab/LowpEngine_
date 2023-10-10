using LowpEngine.AssetsSystem;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace LowpEngine.Loaders
{
    internal static class Assimp
    {
        [DllImport("Engine")]
        private static extern IntPtr Assimp_LoadMesh(string filepath);

        public static Mesh LoadMesh(Asset asset)
        {
            string tempFile = $"{Path.GetTempPath()}{asset.Resource.Name}{asset.Resource.Extension}";
            File.WriteAllBytes(tempFile, asset.Resource.Compressed ? null : asset.Resource.Data);
            IntPtr mesh = IntPtr.Zero;
            mesh = Assimp_LoadMesh(tempFile);
            Thread deletingThread = new Thread(() =>
            {
                File.Delete(tempFile);
            });
            deletingThread.Start();
            Mesh translatedMesh = Marshal.PtrToStructure<Mesh>(mesh);
            translatedMesh.nativeVariant = mesh;
            return translatedMesh;
        }
    }
}
