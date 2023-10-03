using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine
{
    public class Application : IDisposable
    {
        [DllImport("Engine")]
        private static extern IntPtr Application_create();
        [DllImport("Engine")]
        private static extern void  Application_destroy(IntPtr app);
        [DllImport("Engine")]
        private static extern void Application_run(IntPtr app);

        private IntPtr instance;

        public Application()
        {
            instance = Application_create();
        }

        public void Run()
        {
            Application_run(instance);
        }

        public void Dispose()
        {
            Application_destroy(instance);
        }
    }
}
