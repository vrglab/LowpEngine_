using LowpEngine.AssetManagement.Importer;
using LowpEngine.AssetsSystem;
using LowpEngine.AssetSystem.Importer;
using LowpEngine.Loaders;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.Importers
{
    [Importer("obj","fbx")]
    public class MeshImporter : iImporter<Mesh>
    {
        public Mesh Import(Asset resourceFile)
        {
            return Assimp.LoadMesh(resourceFile);
        }
    }
}
