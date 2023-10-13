using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Launcher
{
    public abstract class AssemblyLoadingHandler
    {
        protected abstract string GetAssemblyPath();

        public void Initialize()
        {
            Assembly.LoadFrom(GetAssemblyPath());
        }
    }
}
