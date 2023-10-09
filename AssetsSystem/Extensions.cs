﻿using AssetsSystem.Bundle;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AssetsSystem
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

            // Get the folder that contains the file
            Folder containingFolder = GetFolder(folder, string.Join("/", parts.Take(parts.Length - 1)));

            if (containingFolder != null && containingFolder.DiskResources != null)
            {
                // Check if the file exists in the folder
                if (containingFolder.DiskResources.Contains(fileName))
                {
                    return containingFolder.DiskResources.GetDiskResource(fileName);
                }
                else
                {
                    // If the file with the given name does not exist in the folder, search for files without extensions
                    foreach (var file in containingFolder.DiskResources)
                    {
                        if (Path.GetFileNameWithoutExtension(file.Name) == fileName)
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
            return !Path.HasExtension(path);
        }

        public static bool IsDiskResourcePath(this Folder folder, string path)
        {
            return Path.HasExtension(path);
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
                    Folder newFolder = new Folder { Name = folderName, Parent = currentFolder };
                    currentFolder.Children[folderName] = newFolder;
                }

                currentFolder = currentFolder.Children[folderName];
            }

            string finalFolderName = splitPath.Last();
            currentFolder.Children[finalFolderName] = folderValue;
            folderValue.Name = finalFolderName;
            folderValue.Parent = currentFolder;
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
                containingFolder = new Folder { Name = folderPath, Parent = folder };
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
    }
}