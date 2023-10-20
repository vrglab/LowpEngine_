using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.Scripting
{
    internal static class BehaviourRegistery
    {
        public static List<MonoBehaviour> RegisteredBehaviours { get; private set; }
    }
}
