using GlobalUtilities.IO;
using LowpEngine;
using LowpEngine.AssetsSystem;
using LowpEngine.Debug;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WindowsLauncher;

namespace Launcher
{
    public static class LaunchingManager
    {
         private static Game game = null;

        public static void Launch()
        {
            try
            {
                AssemblyLoadingHandler assemblyLoader = null;

                if (Environment.OSVersion.Platform == PlatformID.Win32NT || Environment.OSVersion.Platform == PlatformID.Win32Windows
                    || Environment.OSVersion.Platform == PlatformID.Win32S || Environment.OSVersion.Platform == PlatformID.WinCE)
                {
                    assemblyLoader = new WindowsAssemblyLoader();
                }

                assemblyLoader.Initialize();
                LaunchInit();
                LaunchLoop();
            }
            catch (Exception e)
            {
                Debug.LogError(e.Message, true);
            }
        }

        private static void LaunchInit()
        {
            string pathToAssetDataBase = $"{Environment.CurrentDirectory}\\Runtimes\\Assets.asset";
            AssetDatabase assets = new AssetDatabase(pathToAssetDataBase);
            IniFile configs = (IniFile)assets["Configs.ini"];

            GameInfo gameInfo = new GameInfo()
            {
                name = configs["Name", "Game"].ToString(),
                assetsLocation = pathToAssetDataBase,
                resHeight = int.Parse(configs["Resolution.y", "Game"].ToString()),
                resWidth = int.Parse(configs["Resolution.y", "Game"].ToString()),
                version = configs["Version", "Game"].ToString(),
                developer = configs["Develper", "Info"].ToString(),
                publisher = configs["Publisher", "Info"].ToString(),
            };
            game = new Game(gameInfo);
        }

        private static void LaunchLoop()
        {
            if (game == null)
                throw new Exception();

            game.Start();
        }
    }
}
