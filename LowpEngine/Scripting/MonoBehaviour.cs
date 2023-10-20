using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.Scripting
{
    public class MonoBehaviour
    {
        public virtual void OnEnable() { }
        public virtual void OnDisable() { }
        public virtual void Awake() { }
        public virtual void Start() { }
        public virtual void Update() { }
        public virtual void OnDestroy() { }
    }
}
