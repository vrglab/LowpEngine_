using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AssetsSystem
{
    public class DiskResource
    {
        public byte[] Data { get; }
        public string Name { get; }
        public string Extension { get; }
        public bool Compressed { get; }

        public DiskResource(byte[] data, string name, string extension, bool compressed)
        {
            Data = data;
            Name = name;
            Extension = extension;
            Compressed = compressed;
        }
    }
}
