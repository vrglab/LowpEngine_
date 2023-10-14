using MessagePack;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.AssetsSystem.Bundle
{
    [MessagePackObject]
    public class Folder
    {
        [Key(0)]
        public string Name { get; set; }
        [Key(1)]
        public string PathFromRoot { get; set; }
        [Key(2)]
        public Folder Parent { get; set; }
        [Key(3)]
        public Dictionary<string, Folder> Children { get; set;} = new Dictionary<string, Folder>();
        [Key(4)]
        public List<DiskResource> DiskResources { get; set;} = new List<DiskResource>();

        [SerializationConstructor]
        public Folder(string name, string pathFromRoot, Folder parent, Dictionary<string, Folder> children, List<DiskResource> diskResources)
        {
            Name = name;
            PathFromRoot = pathFromRoot;
            Parent = parent;
            Children = children;
            DiskResources = diskResources;
        }

        public Folder()
        {
        }
    }
}
