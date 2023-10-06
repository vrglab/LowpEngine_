using LowpEngine;
using LowpEngine.Debug;

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
                resWidth = 400,
                resHeight = 600,
            };
            Game exampleGame = new Game(gameInfo);
            exampleGame.Start();
        }
    }
}
