using LowpEngine.Types.Mathmatics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine
{
    public class Mesh
    {
        public List<Vector3> vertices;
        public List<Vector3> normals;
        public List<Vector2> textureCoords;
        public List<int> indices;
        public List<Mesh> submeshes;

        public IntPtr nativeVariant;

        public Mesh(List<Vector3> vertices, List<Vector3> normals, List<Vector2> textureCoords, List<int> indices, IntPtr native_variant)
        {
            this.vertices = vertices;
            this.normals = normals;
            this.textureCoords = textureCoords;
            this.indices = indices;
            submeshes = new List<Mesh>();
            this.nativeVariant = native_variant;
        }

        public Mesh()
        {
            this.vertices = new List<Vector3>();
            this.normals = new List<Vector3>();
            this.textureCoords = new List<Vector2>();
            this.indices = new List<int>();
            submeshes = new List<Mesh>();
            nativeVariant = IntPtr.Zero;
        }

        ~Mesh()
        {
            Marshal.FreeHGlobal(nativeVariant);
        }

        public void AddSubMesh(Mesh subMesh)
        {
            submeshes.Add(subMesh);
        }
    }
}
