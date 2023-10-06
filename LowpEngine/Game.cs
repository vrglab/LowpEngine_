using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static LowpEngine.Application;

namespace LowpEngine
{
    public class Game
    {

        private Application app;
        private GameInfo gameInfo;

        public string PersistentDataPath { get => $"{Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData)}\\{gameInfo.name}"; }

        public event Update OnUpdate;

        public Game(GameInfo gameInfo)
        {
            this.gameInfo = gameInfo;
            app = new Application(gameInfo.name);
        }

        public void Start()
        {
            Debug.Debug.Log("Starting Engine");
            Debug.Debug.Log($"Starting {gameInfo.name} by {gameInfo.developer} version {gameInfo.version}");
            app.OnUpdate += OnUpdate;
            app.OnUpdate += Update;
            try
            {
                app.Run();
            }
            catch (Exception ex)
            {
                Debug.Debug.LogError("There was a error: " + ex.Message);
            }
            Debug.Debug.Log("Closing Engine");
            GC.Collect();
        }

        private void Update()
        {

        }
    }

    public struct GameInfo
    {
        public string name;
        public string version;
        public string developer;
        public string publisher;
    }
}
