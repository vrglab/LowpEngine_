using LowpEngine.AssetsSystem;
using LowpEngine.AssetsSystem.Bundle;
using LowpEngine.Utility;
using MessagePack;
using MessagePack.Resolvers;
using System;
using System.Collections.Generic;
using System.IO;

namespace LowpEngine.AssetsSystem
{
    public class AssetsDatabase
    {

        internal AssetLoader assetsLoader { get => GetAssetsLoader(); set { assetsloader = value; } }
        private AssetLoader assetsloader;

        private AssetLoader GetAssetsLoader()
        {
            if (assetsloader == null)
            {
                assetsloader = new AssetLoader();
            }
            return assetsloader;
        }


        internal AssetsImporter assetsImporter { get => GetAssetsImporter(); private set { assetsimporter = value; } }
        private AssetsImporter assetsimporter;

        private AssetsImporter GetAssetsImporter()
        {
            if (assetsimporter == null)
            {
                assetsimporter = new AssetsImporter();
            }
            return assetsimporter;
        }


        public object ImportAsset(string path)
        {
            return assetsImporter[assetsLoader[path]];
        }

        public void LoadAssetBundle(string path)
        {
            if (AssetsBundle.IsDiskResourcePath(path))
            {
                byte[] bytes = Utils.Decompress(File.ReadAllBytes(path));
                AssetsBundle ab =
                    MessagePackSerializer.Deserialize<AssetsBundle>(bytes, ContractlessStandardResolver.Options);

                assetsLoader._asset_bundle_file = ab;
            }
            else if(AssetsBundle.IsFolderPath(path))
            {
                Folder convertedFolder = AssetsBundle.GetFolder(path);
                assetsLoader._asset_bundle_file = new AssetsBundle(convertedFolder);
            }
        }
    }
}
