using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.AssetsSystem.Bundle
{
    public class AssetsBundle
    {
        private Folder root = new Folder()
        {
            Name = "Root",
            PathFromRoot = "Root"
        };

        public object this[string path] { get { return GetBasedOnPath(path); }
            set { SetBasedOnPath(path, value); }
        }

        public AssetsBundle()
        {

        }

        public AssetsBundle(Folder addToroot)
        {
            addToroot.Parent = root;
            root.Children[addToroot.PathFromRoot] = addToroot;
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

        public static Folder GetFolder(string folderPath, bool compressed = false, Folder parent = null, string pathFromRoot = "Root")
        {
            if (Directory.Exists(folderPath))
            {
                DirectoryInfo directoryInfo = new DirectoryInfo(folderPath);
                Folder folder = new Folder();
                folder.PathFromRoot = $"{pathFromRoot}\\{directoryInfo.Name}";
                folder.Name = directoryInfo.Name;
                folder.Parent = parent;

                foreach (FileInfo file in directoryInfo.GetFiles())
                {
                    folder.DiskResources.Add(GetFile(file.FullName, compressed));
                }

                foreach (DirectoryInfo childs in directoryInfo.GetDirectories())
                {
                    folder.Children[$"{folder.PathFromRoot}\\{childs.Name}"] = GetFolder(childs.FullName, compressed, folder, folder.PathFromRoot);
                }
                return folder;
            }
            return null;
        }

        public static DiskResource GetFile(string path, bool compressed)
        {
            if (File.Exists(path))
            {
                return new DiskResource(File.ReadAllBytes(path), Path.GetFileNameWithoutExtension(path), Path.GetExtension(path), compressed);
            }
            else
            {
                Console.WriteLine($"\"{path}\" is not a valid file");
                return null;
            }
        }
    }
}
