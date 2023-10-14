using LowpEngine.Utility;
using MessagePack;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.AssetsSystem.Bundle
{
    [MessagePackObject]
    public class AssetsBundle
    {
        [Key(1)]
        public Folder root { get; private set; } = new Folder()
        {
            Name = "Root",
            PathFromRoot = "Root"
        };

        [IgnoreMember]  
        public object this[string path] { get { return GetBasedOnPath(path); }
            set { SetBasedOnPath(path, value); }
        }

        [SerializationConstructor]
        public AssetsBundle(Folder addToroot)
        {
            if (addToroot.Name == "Root")
            {
                root = addToroot;
            }
            else
            {
                addToroot.PathToParent = root.PathFromRoot;
                root.Children[addToroot.PathFromRoot] = addToroot;
            }
            
        }

        public AssetsBundle()
        {

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
                folder.PathToParent = (parent == null ) ? string.Empty : parent.PathFromRoot;

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
                return new DiskResource(compressed ? Utils.Compress(File.ReadAllBytes(path)) : File.ReadAllBytes(path), Path.GetFileNameWithoutExtension(path), Path.GetExtension(path), compressed);
            }
            else
            {
                Console.WriteLine($"\"{path}\" is not a valid file");
                return null;
            }
        }

        public static bool IsFolderPath(string path)
        {
            return !Path.HasExtension(path);
        }

        public static bool IsDiskResourcePath(string path)
        {
            return Path.HasExtension(path);
        }
    }
}
