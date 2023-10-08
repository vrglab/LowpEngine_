using ConsoleAppEngine;
using System;
using System.Collections.Generic;
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
                Console.WriteLine($"Successfully created and compressed \"{args[0]}\" to \"{assetFile}\"");
            }
            else
            {
                Console.WriteLine($"Successfully created \"{args[0]}\" to \"{assetFile}\"");
            }
        }
    }
}
