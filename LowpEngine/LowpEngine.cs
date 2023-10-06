using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static LowpEngine.Application;

namespace LowpEngine
{
    public static class LowpEngine
    {
        private static Application app = new Application();

        public static event Update OnUpdate;

        public static void Run()
        {
            Debug.Debug.Log("Starting Engine");
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

        private static void Update()
        {

        }
    }
}
