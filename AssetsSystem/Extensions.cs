using LowpEngine.AssetsSystem.Bundle;
using LowpEngine.Utility;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.AssetsSystem
{
    public static class Extensions
    {
        public static Folder GetFolder(this Folder folder, string path)
        {
            string[] splitPath = path.Split('/');

            if(splitPath.Length == 1)
            {
                splitPath = path.Split('\\');
            }

            Folder currentFolder = folder;

            foreach (string folderName in splitPath)
            {
                if (currentFolder.Children != null && currentFolder.Children.Contains(folderName))
                {
                    currentFolder = currentFolder.Children.GetFolder(folderName);
                }
                else
                {

                    return null;
                }
            }

            return currentFolder;
        }

        public static DiskResource GetFile(this Folder folder, string path)
        {
            // Split the path into folder names and the file name
            string[] parts = path.Split('/');
            string fileName = parts[parts.Length - 1]; // Last part is the file name

            string pathToFolder = string.Join("/", parts.Take(parts.Length - 1));


            // Get the folder that contains the file
            Folder containingFolder = GetFolder(folder, pathToFolder);

            if (containingFolder != null && containingFolder.DiskResources != null)
            {
                // Check if the file exists in the folder
                if (containingFolder.DiskResources.Contains(Path.GetFileNameWithoutExtension(fileName)))
                {
                    return containingFolder.DiskResources.GetDiskResource(Path.GetFileNameWithoutExtension(fileName));
                }
                else
                {
                    // If the file with the given name does not exist in the folder, search for files without extensions
                    foreach (var file in containingFolder.DiskResources)
                    {
                        if (Path.GetFileNameWithoutExtension(file.Name) == Path.GetFileNameWithoutExtension(fileName))
                        {
                            return file;
                        }
                    }
                }
            }

            // If the file was not found, return null
            return default;
        }

        public static bool IsFolderPath(this Folder folder, string path)
        {
            return AssetsBundle.IsFolderPath(path);
        }

        public static bool IsDiskResourcePath(this Folder folder, string path)
        {
            return AssetsBundle.IsDiskResourcePath(path);
        }

        public static bool IsFolderExists(this Folder folder, string path)
        {
            Folder result = GetFolder(folder, path);
            return result != null;
        }

        public static bool IsDiskResourceExists(this Folder folder, string path)
        {
            DiskResource result = GetFile(folder, path);
            return result != null;
        }

        public static void SetFolderUsingPath(this Folder folder, string path, Folder folderValue)
        {
            string[] splitPath = path.Split('/');
            Folder currentFolder = folder;

            for (int i = 0; i < splitPath.Length - 1; i++)
            {
                string folderName = splitPath[i];
                if (!currentFolder.Children.ContainsKey(folderName))
                {
                    // Create a new folder if it doesn't exist
                    Folder newFolder = new Folder { Name = folderName, PathToParent = currentFolder.PathFromRoot };
                    currentFolder.Children[folderName] = newFolder;
                }

                currentFolder = currentFolder.Children[folderName];
            }

            string finalFolderName = splitPath.Last();
            currentFolder.Children[finalFolderName] = folderValue;
            folderValue.Name = finalFolderName;
            folderValue.PathToParent = currentFolder.PathFromRoot;
        }

        public static void SetDiskResourceUsingPath(this Folder folder, string path, DiskResource resourceValue)
        {
            string[] parts = path.Split('/');
            string fileName = parts.Last(); // Last part is the file name
            string folderPath = string.Join("/", parts.Take(parts.Length - 1)); // Path to the folder containing the file

            // Get the folder that contains the file or create it if it doesn't exist
            Folder containingFolder = folder.GetFolder(folderPath);
            if (containingFolder == null)
            {
                containingFolder = new Folder { Name = folderPath, PathToParent = folder.PathFromRoot };
                folder.SetFolderUsingPath(folderPath, containingFolder);
            }

            containingFolder.DiskResources.Add(resourceValue);
        }

        public static DiskResource GetDiskResource(this List<DiskResource> fileList, string name)
        {
            foreach (DiskResource resource in fileList)
            {
                if(resource.Name == name)
                {
                    return resource;
                }
            }
            return null;
        }

        public static bool Contains(this List<DiskResource> fileList, string name)
        {
            foreach (DiskResource resource in fileList)
            {
                if (resource.Name == name)
                {
                    return true;
                }
            }
            return false;
        }

        public static Folder GetFolder(this Dictionary<string, Folder> folders, string name)
        {
            foreach (var resource in folders)
            {
                if (resource.Value.Name == name)
                {
                    return resource.Value;
                }
            }
            return null;
        }

        public static bool Contains(this Dictionary<string, Folder> folders, string name)
        {
            foreach (var resource in folders)
            {
                if (resource.Value.Name == name)
                {
                    return true;
                }
            }
            return false;
        }

        public static void ConvertBundleToDirectory(this AssetsBundle bundle, string outputPath)
        {
            if (bundle == null)
            {
                throw new ArgumentNullException("bundle");
            }

            if (outputPath == null)
            {
                throw new ArgumentNullException("outputPath");
            }

            if (!Directory.Exists(outputPath))
            {
                Directory.CreateDirectory(outputPath);
            }

            ConvertFolder(bundle.root, outputPath);
        }

        private static void ConvertFolder(Folder folder, string outputPath)
        {
            string folderPath = Path.Combine(outputPath, folder.PathFromRoot);

            // Create the directory for the current folder
            Directory.CreateDirectory(folderPath);

            // Convert and save disk resources
            foreach (var resource in folder.DiskResources)
            {
                string filePath = Path.Combine(folderPath, resource.Name + resource.Extension);

                if (resource.Compressed)
                {
                    // Decompress and save the compressed resource
                    File.WriteAllBytes(filePath, Utils.Decompress(resource.Data));
                }
                else
                {
                    // Save the uncompressed resource
                    File.WriteAllBytes(filePath, resource.Data);
                }
            }

            // Recursively convert child folders
            foreach (var childFolder in folder.Children.Values)
            {
                ConvertFolder(childFolder, outputPath);
            }
        }
    }
}
