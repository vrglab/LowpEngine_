using log4net;
using log4net.Config;
using log4net.Core;
using log4net.Repository;
using log4net.Repository.Hierarchy;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.Debug
{
    internal class debug 
    {
        public static readonly ILog log = LogManager.GetLogger(typeof(Debug));
        public debug()
        {
            BasicConfigurator.Configure();
        }
    }


    public static class Debug
    {
        private static debug logger = new debug();
        public static void Log(string message)
        {
            debug.log.Info(message);
        }

        public static void LogError(string message)
        {
            debug.log.Error(message);
        }

        public static void LogWarning(string message)
        {
            debug.log.Warn(message);
        }
    }
}
