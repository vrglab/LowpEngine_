using LowpEngine.AssetsSystem;
using LowpEngine.AssetsSystem.Bundle;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.AssetSystem
{
    public class AssetLoader
    {
        public Asset this[string path] { 
            get {
                return GetAsset(path);
            }

            set { 
                if(value is Asset)
                {
                    _loaded_assets[path] = value;
                }
            }
        }

        private Dictionary<string, Asset> _loaded_assets = new Dictionary<string, Asset>();
        internal AssetsBundle _asset_bundle_file;

        public AssetLoader()
        {

        }

        public void SetAssetBundle(AssetsBundle assetBundleFile)
        {
            _asset_bundle_file = assetBundleFile;
        }

        private Asset GetAsset(string path)
        {
            if(_loaded_assets.ContainsKey(path))
            {
                return _loaded_assets[path];    
            } else
            {
                DiskResource rf = (DiskResource)_asset_bundle_file[path];
                Asset resource = new(rf, null, new Dictionary<string, object>());
                 _loaded_assets[path] = resource;
                 return resource;
            }
        }
    }

    public class AssetFolderLoader
    {
        public Folder this[string path]
        {
            get
            {
                return GetFolder(path);
            }

            set
            {
                if (value is Folder)
                {
                    _loaded_assets[path] = value;
                }
            }
        }

        private Dictionary<string, Folder> _loaded_assets = new Dictionary<string, Folder>();
        private AssetsBundle _asset_bundle_file;

        public AssetFolderLoader()
        {
            AssetsBundle abf_data = null;


            _asset_bundle_file = abf_data;
        }

        private Folder GetFolder(string path)
        {
            if (_loaded_assets.ContainsKey(path))
            {
                return _loaded_assets[path];
            }
            else
            {
                return (Folder)_asset_bundle_file[path];
            }
        }
    }
}
