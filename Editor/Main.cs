using LowpEngine;
using LowpEngine.Debug;
using System;

namespace Editor
{
    internal class main
    {
        public static void Main(string[] args)
        {
            GameInfo gameInfo = new GameInfo()
            {
                name = "Example name",
                developer = "Vrglab",
                publisher = "No one",
                resHeight = 400,
                resWidth = 600,
                assetsLocation = "",
                version = "Beta"
            };
            Game g = new Game(gameInfo);
            g.Start();
        }
    }
}
