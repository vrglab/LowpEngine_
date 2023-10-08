using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AssetsSystem.Bundle
{
    public class Folder
    {
        public string Name { get; set; }
        public Folder Parent { get; set; }
        public Dictionary<string, Folder> Children { get; set;} = new Dictionary<string, Folder>();
        public Dictionary<string, DiskResource> DiskResources { get; set;} = new Dictionary<string, DiskResource>();
    }
}
