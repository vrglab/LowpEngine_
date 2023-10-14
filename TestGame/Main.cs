using LowpEngine;
using LowpEngine.Debug;
using System;


internal class main
{
    public static void Main(string[] args)
    {
        GameInfo gameInfo = new GameInfo()
        {
            name = "Lol",
            developer = "Example Dev",
            version = "1.0.0-beta",
            resHeight = 400,
            resWidth = 600,
            assetsLocation = "D:\\Reusable Unity assets\\3D spesific assets\\Assets.asb",
            flags = 0
        };
        Game game = new Game(gameInfo);
        game.Start();
    }
}
