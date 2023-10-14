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
        [Key(1)]
        public string Name { get; set; }
        [Key(2)]
        public string PathFromRoot { get; set; }
        [Key(3)]
        public string PathToParent { get; set; }
        [Key(4)]
        public Dictionary<string, Folder> Children { get; set;} = new Dictionary<string, Folder>();
        [Key(5)]
        public List<DiskResource> DiskResources { get; set;} = new List<DiskResource>();

        [SerializationConstructor]
        public Folder(string name, string pathFromRoot, string parent, Dictionary<string, Folder> children, List<DiskResource> diskResources)
        {
            Name = name;
            PathFromRoot = pathFromRoot;
            PathToParent = parent;
            Children = children;
            DiskResources = diskResources;
        }

        public Folder()
        {
        }
    }
}
