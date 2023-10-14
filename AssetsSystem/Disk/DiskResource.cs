using MessagePack;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.AssetsSystem
{
    [MessagePackObject]
    public class DiskResource
    {
        [Key(1)]
        public byte[] Data { get; }
        [Key(2)]
        public string Name { get; }
        [Key(3)]
        public string Extension { get; }
        [Key(4)]
        public bool Compressed { get; }

        [SerializationConstructor]
        public DiskResource(byte[] data, string name, string extension, bool compressed)
        {
            Data = data;
            Name = name;
            Extension = extension;
            Compressed = compressed;
        }
    }
}
