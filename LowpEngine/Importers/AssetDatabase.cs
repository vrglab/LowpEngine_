using LowpEngine.AssetsSystem;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.AssetsSystem
{
    public class AssetDatabase
    {
        public object this[string path]
        {
            get
            {
                return database.ImportAsset(path);
            }
        }

        private LowpEngine.AssetsSystem.AssetsDatabase database;

        public AssetDatabase(string assetsBundle)
        {
            this.database = new LowpEngine.AssetsSystem.AssetsDatabase();
            database.LoadAssetBundle(assetsBundle);
        }

        public AssetDatabase()
        {
            this.database = new LowpEngine.AssetsSystem.AssetsDatabase();
        }
    }
}
