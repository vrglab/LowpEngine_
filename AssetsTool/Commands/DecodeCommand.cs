using ConsoleAppEngine;
using LowpEngine.AssetsSystem;
using LowpEngine.AssetsSystem.Bundle;
using LowpEngine.Utility;
using MessagePack;
using MessagePack.Resolvers;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AssetsTool.Commands
{

    [Command("decode", 2,  "fn")]
    [HelpCommandData("Decodes the given .asset file into a folder",
        new string[] { "File To Convert", "Where to save the folder" },
        validOptionNames = new string[] { "fn" },
        validOptionValue = new string[] { "Folder name" })]
    public class DecodeCommand : ICommand
    {
        public void Execute(string[] args, KeyValuePair<string, string>[] options)
        {
            string FolderName = options.Contains("fn") ? options.GetOptionValue("fn") : "Asset";
            string folderDir = $"{args[1]}/{FolderName}";

            byte[] bytes = Utils.Decompress(File.ReadAllBytes(args[0]));

            AssetsBundle assetBundle = MessagePackSerializer.Deserialize<AssetsBundle>(bytes, ContractlessStandardResolver.Options);
        }
    }
}
