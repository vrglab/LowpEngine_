﻿using LowpEngine.AssetsSystem;
using LowpEngine.AssetSystem;
using LowpEngine.Debug;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using static LowpEngine.Application;

namespace LowpEngine
{
    public class Game
    {

        private Application app;
        private GameInfo gameInfo;
        private IntPtr engineLib;

        public string PersistentDataPath { get => $"{Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData)}\\{gameInfo.name}"; }

        public AssetDatabase assetDatabase { get;}

        public event Update OnUpdate;

        public Game(GameInfo gameInfo)
        {
            engineLib = LoadLibrary(Path.Combine(Environment.CurrentDirectory, "Engine.dll"));
            this.gameInfo = gameInfo;
            try
            {
                assetDatabase = new AssetDatabase(gameInfo.assetsLocation);
            }
            catch (Exception e)
            {
                assetDatabase = new AssetDatabase();
            }
            
            app = new Application(gameInfo);
        }

        ~Game()
        {
            FreeLibrary(engineLib);
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
                Debug.Debug.LogError("There was a error: " + ex.Message, true);
            }
            Debug.Debug.Log("Closing Engine");
            GC.Collect();
        }

        public void Stop()
        {
            app.Stop();
        }

        private void Update()
        {

        }

        [DllImport("kernel32.dll")]
        private static extern IntPtr LoadLibrary(string dllToLoad);

        [DllImport("kernel32.dll")]
        private static extern bool FreeLibrary(IntPtr hModule);
    }

    public struct GameInfo
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
        public string name;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
        public string version;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
        public string developer;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
        public string publisher;

        public int resWidth, resHeight;
        public WindowFlags flags;

        public string assetsLocation;
    }

    public enum WindowFlags
    {
        Fullscreen = 1,
        Resizable = 32,
        fullscreen_desktop = 4096,
        Hidden = 9, Borderless = 16, Minimized = 64, Maximized = 128
    }
}
