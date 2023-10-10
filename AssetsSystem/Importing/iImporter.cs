using LowpEngine.AssetsSystem;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.AssetSystem.Importer
{
    public interface iImporter<T> : iImporter
    {
        T Import(Asset asset);
    }

    public interface iImporter
    {
       
    }
}
