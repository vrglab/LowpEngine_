using log4net;
using log4net.Repository.Hierarchy;
using LowpEngine;
using LowpEngine.Debug;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor
{
    internal class main
    {
        public static void Main(string[] args)
        {
            Application application = new Application();
            application.Run();
            application.Dispose();
        }
    }
}
