using LowpEngine;
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
                    version = "1.0.0-beta",
                    resHeight = 400,
                    resWidth = 600,
                    assetsLocation = "D:\\IntelliJ projects\\WeserGamesEngine\\src\\test\\resources\\Meshes"
                };
                Game exampleGame = new Game(gameInfo);
                Mesh mesh = (Mesh)exampleGame.assetDatabase["Meshes/dragon.obj"];
                exampleGame.Start();
            }
            catch (Exception e)
            {
                Debug.LogError(e.Message, true);
            }
        }
    }
}
