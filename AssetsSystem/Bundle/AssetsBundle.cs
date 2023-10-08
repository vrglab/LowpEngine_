using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace AssetsSystem.Bundle
{
    public class AssetsBundle
    {
        private Folder root = new Folder()
        {
            Name = "Root"
        };
        public object this[string path] { get { return GetBasedOnPath(path); }
            set { SetBasedOnPath(path, value); }
        }

        private void SetBasedOnPath(string path, object value)
        {
            if (root.IsDiskResourcePath(path))
            {
                 root.SetDiskResourceUsingPath(path, (DiskResource)value);
            }

            if (root.IsFolderPath(path))
            {
                root.SetFolderUsingPath(path, (Folder)value);
            }
        }

        private object GetBasedOnPath(string path)
        {
            if (root.IsDiskResourcePath(path))
            {
                return root.GetFile(path);
            }

            if (root.IsFolderPath(path))
            {
                return root.GetFolder(path);
            }

            return null;
        }
    }
}
