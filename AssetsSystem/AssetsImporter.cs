using LowpEngine.AssetManagement.Importer;
using LowpEngine.AssetsSystem;
using LowpEngine.Utility;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.AssetSystem
{
    public class AssetsImporter
    {
        public object this[Asset path]
        {
            get
            {
                return GetResource(path);
            }
        }

        private Dictionary<string, object> _loaded_assets = new Dictionary<string, object>();


        private object GetResource(Asset asset)
        {
            if(_loaded_assets.ContainsKey(asset.Id.ToString()))
            {
                return _loaded_assets[asset.Id.ToString()];
            }
            else
            {
                Type importerType = null; 
                foreach (var item in Utils.GetTypesMarkedWithAttrib(typeof(ImporterAttribute)))
                {
                    ImporterAttribute atrib = item.GetCustomAttribute<ImporterAttribute>();
                    if (atrib.FileExtension.Contains(asset.Resource.Extension))
                    {
                        importerType = item;
                    }
                }
                if(importerType == null)
                {
                    return null;
                }
                object importedData = null;
                if (importerType.GetInterface("iImporter") != null)
                {
                    var importer = importerType.GetConstructor(new Type[] { }).Invoke(new object[] {});
                    importedData = importerType.GetMethod("Import").Invoke(importer, new object[] { asset.Resource });
                }
                _loaded_assets[asset.Id.ToString()] = importedData;
                return importedData;
            }
        }
    }
}
