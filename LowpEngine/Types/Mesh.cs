using LowpEngine.Types.Mathmatics;
using System;
using System.Collections.Generic;
using System.Linq;
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

        public Mesh(List<Vector3> vertices, List<Vector3> normals, List<Vector2> textureCoords, List<int> indices)
        {
            this.vertices = vertices;
            this.normals = normals;
            this.textureCoords = textureCoords;
            this.indices = indices;
            submeshes = new List<Mesh>();
        }

        public void AddSubMesh(Mesh subMesh)
        {
            submeshes.Add(subMesh);
        }
    }
}
