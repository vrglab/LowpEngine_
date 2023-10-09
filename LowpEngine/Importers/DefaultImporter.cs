using LowpEngine.AssetManagement.Importer;
using LowpEngine.AssetsSystem;
using LowpEngine.AssetSystem.Importer;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.Importers
{
    [Importer("*")]
    public class DefaultImporter : iImporter<string>
    {
        public string Import(DiskResource resourceFile)
        {
            return Encoding.Default.GetString(resourceFile.Data);
        }
    }
}
