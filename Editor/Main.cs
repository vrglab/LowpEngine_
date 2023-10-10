using LowpEngine;
using LowpEngine.AssetSystem;
using LowpEngine.Debug;
using System;

namespace Editor
{
    internal class main
    {
        public static void Main(string[] args)
        {
            try
            {
                GameInfo gameInfo = new GameInfo()
                {
                    name = "Lol",
                    developer = "Example Dev",
                    version = "1.0.0-resWidth = 600",
                    resHeight = 400,
                };
                Game exampleGame = new Game(gameInfo);
                AssetsDatabase.LoadAssetBundle("D:\\IntelliJ projects\\WeserGamesEngine\\src\\test\\resources\\Meshes");
                Mesh mesh = (Mesh)AssetsDatabase.ImportAsset("Meshes/dragon.obj");
                exampleGame.Start();
            }
            catch (Exception e)
            {
                Debug.LogError(e.Message, true);
            }
        }
    }
}
