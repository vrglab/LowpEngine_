using AssetsSystem;
using AssetsSystem.Bundle;
using ConsoleAppEngine;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AssetsTool.Commands
{
    [Command("encode", 2, "comp", "fn")]
    [HelpCommandData("Encodes the given folder into a .asset file", 
        new string[]{"Folder To Convert", "Where to save the .asset file"}, 
        validOptionNames = new string[] {"comp", "fn"}, 
        validOptionValue = new string[] { "Compress file", "File name" })]
    public class EncodeCommand : ICommand
    {
        public void Execute(string[] args, KeyValuePair<string, string>[] options)
        {
            bool Compress = options.Contains("comp");
            string assetFileName = options.Contains("fn") ? options.GetOptionValue("fn") : "Asset";
            string assetFile = $"{args[1]}/{assetFileName}.asset";

            if (Compress)
            {
                DiskResource diskResource = new DiskResource(null, "", "", true);
                Console.WriteLine($"Successfully created and compressed \"{args[0]}\" in to \"{assetFile}\"");
            }
            else
            {
                
                Folder convertedFolder = AssetsBundle.GetFolder(args[0]);
                AssetsBundle ab = new AssetsBundle(convertedFolder);
                Folder project = (Folder)ab["LowpProjects/test"];
                Console.WriteLine($"Successfully put \"{args[0]}\" in to \"{assetFile}\"");
            }
        }
    }
}
