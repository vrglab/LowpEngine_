using LowpEngine.AssetsSystem;
using LowpEngine.Utility;
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
            File.WriteAllBytes(tempFile, asset.Resource.Compressed ? Utils.Decompress(asset.Resource.Data) : asset.Resource.Data);
            IntPtr mesh = IntPtr.Zero;
            mesh = Assimp_LoadMesh(tempFile);
            Thread deletingThread = new Thread(() =>
            {
                File.Delete(tempFile);
            });
            deletingThread.Start();
            MeshCreationInformation info = Marshal.PtrToStructure<MeshCreationInformation>(mesh);
            Mesh translatedMesh = new Mesh(info.vertices, info.normals, info.textureCoords, info.indices, mesh);
            translatedMesh.nativeVariant = mesh;
            return translatedMesh;
        }
    }
}
