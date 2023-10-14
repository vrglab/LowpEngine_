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
            resHeight = 1000,
            resWidth = 600,
            assetsLocation = "D:\\Reusable Unity assets\\3D spesific assets\\Assets.asb",
            flags = WindowFlags.Resizable | WindowFlags.Borderless
        };
        Game game = new Game(gameInfo);
        game.Start();
    }
}
