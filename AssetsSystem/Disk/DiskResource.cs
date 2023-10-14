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
        [Key(0)]
        public byte[] Data { get; }
        [Key(1)]
        public string Name { get; }
        [Key(2)]
        public string Extension { get; }
        [Key(3)]
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
