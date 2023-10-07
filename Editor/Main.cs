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
                name = "Lol",
                developer = "Example Dev",
                version = "1.0.0-Beta",
                resWidth = 600,
                resHeight = 400,
            };
            Game exampleGame = new Game(gameInfo);
            exampleGame.Start();
        }
    }
}
