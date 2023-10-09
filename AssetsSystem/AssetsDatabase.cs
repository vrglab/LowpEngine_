using LowpEngine.AssetsSystem.Bundle;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.AssetSystem
{
    public static class AssetsDatabase
    {

        internal static AssetLoader assetsLoader { get => GetAssetsLoader(); set { assetsloader = value; } }
        private static AssetLoader assetsloader;

        private static AssetLoader GetAssetsLoader()
        {
            if (assetsloader == null)
            {
                assetsloader = new AssetLoader();
            }
            return assetsloader;
        }


        internal static AssetsImporter assetsImporter { get => GetAssetsImporter(); private set { assetsimporter = value; } }
        private static AssetsImporter assetsimporter;

        private static AssetsImporter GetAssetsImporter()
        {
            if (assetsimporter == null)
            {
                assetsimporter = new AssetsImporter();
            }
            return assetsimporter;
        }


        public static object ImportAsset(string path)
        {
            return assetsImporter[assetsLoader[path]];
        }

        public static void LoadAssetBundle(string path)
        {
            Folder convertedFolder = AssetsBundle.GetFolder(path);
            assetsLoader._asset_bundle_file = new AssetsBundle(convertedFolder);
        }
    }
}
