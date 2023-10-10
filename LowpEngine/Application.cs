﻿using LowpEngine.AssetSystem;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine
{
    public class Application
    {
        [DllImport("Engine.dll")]
        private static extern IntPtr Application_create(GameInfo gameinfo);
        [DllImport("Engine")]
        private static extern void  Application_destroy(IntPtr app);
        [DllImport("Engine")]
        private static extern void Application_init(IntPtr app);
        [DllImport("Engine")]
        private static extern void Application_stop(IntPtr app);
        [DllImport("Engine")]
        private static extern void Application_run(IntPtr app, Update update);

        private IntPtr instance;

        public delegate void Update();
        public event Update OnUpdate;


        public Application(GameInfo gameinfo)
        {
            instance = Application_create(gameinfo);
        }

        ~Application()
        {
            Application_destroy(instance);
        }

        public void Run()
        {
            Application_init(instance);
            Application_run(instance, OnUpdate);
        }

        public void Stop()
        {
            Application_stop(instance);
        }
    }
}
