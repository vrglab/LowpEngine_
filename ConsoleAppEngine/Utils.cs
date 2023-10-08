﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleAppEngine
{
    public static class Utils
    {
        public static List<Type> GetTypesMarkedWithAttrib(Type TestType)
        {
            Assembly[] assemblies = AppDomain.CurrentDomain.GetAssemblies();
            List<Type> types = new List<Type>();
            foreach (Assembly assembly in assemblies)
            {
                var classesWithAttribute = assembly.GetTypes()
                    .Where(type => type.GetCustomAttributes(TestType, true).Length > 0)
                    .ToList();
                foreach (var classType in classesWithAttribute)
                {
                    types.Add(classType);
                }
            }
            return types;
        }

        public static List<Type> GetTypesMarkedWithAttrib(Type TestType, Assembly assembly)
        {
            List<Type> types = new List<Type>();
            var classesWithAttribute = assembly.GetTypes()
                .Where(type => type.GetCustomAttributes(TestType, true).Length > 0)
                .ToList();
            foreach (var classType in classesWithAttribute)
            {
                types.Add(classType);
            }
            return types;
        }

        public static List<string> FindFiles(string directory, string searchFileName)
        {
            List<string> foundFiles = new List<string>();

            try
            {
                // Get a list of all files in the current directory that match the search criteria
                string[] files = Directory.GetFiles(directory, searchFileName, SearchOption.TopDirectoryOnly);
                foundFiles.AddRange(files);

                // Recursively search subdirectories
                string[] subdirectories = Directory.GetDirectories(directory);

                foreach (string subdirectory in subdirectories)
                {
                    List<string> subdirectoryFiles = FindFiles(subdirectory, searchFileName);
                    foundFiles.AddRange(subdirectoryFiles);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }

            return foundFiles;
        }

        public static string GetTargetOsForBuild()
        {
            return "Windows";
        }
    }

    public static class Extensions
    {
        public static string RemoveTabbing(this string fmt)
        {
            return string.Join(
                System.Environment.NewLine,
                fmt.Split(new string[] { System.Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries)
                    .Select(fooline => fooline.Trim()));
        }
    }
}