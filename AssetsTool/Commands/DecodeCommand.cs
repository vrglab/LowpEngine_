using ConsoleAppEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AssetsTool.Commands
{

    [Command("decode", 2, "decomp", "fn")]
    [HelpCommandData("Decodes the given .asset file into a folder",
        new string[] { "File To Convert", "Where to save the folder" },
        validOptionNames = new string[] { "decomp", "fn" },
        validOptionValue = new string[] { "Decompress file", "Folder name" })]
    public class DecodeCommand : ICommand
    {
        public void Execute(string[] args, KeyValuePair<string, string>[] options)
        {
            
        }
    }
}
