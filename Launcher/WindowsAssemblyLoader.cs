using Launcher;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsLauncher
{
    public class WindowsAssemblyLoader : AssemblyLoadingHandler
    {
        protected override string GetAssemblyPath()
        {
            return $"{Environment.CurrentDirectory}\\Runtime\\AssemblyGame.dll";
        }
    }
}
