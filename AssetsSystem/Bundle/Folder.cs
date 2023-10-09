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
        public string PathFromRoot { get; set; }
        public Folder Parent { get; set; }
        public Dictionary<string, Folder> Children { get; set;} = new Dictionary<string, Folder>();
        public List<DiskResource> DiskResources { get; set;} = new List<DiskResource>();


        
    }
}
