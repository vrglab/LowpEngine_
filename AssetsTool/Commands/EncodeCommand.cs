using LowpEngine.AssetsSystem.Bundle;
using ConsoleAppEngine;
using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;
using LowpEngine.Utility;
using MessagePack;
using MessagePack.Resolvers;

namespace AssetsTool.Commands
{
    [Command("encode", 2,  "fn")]
    [HelpCommandData("Encodes the given folder into a .asset file", 
        new string[]{"Folder To Convert", "Where to save the .asset file"}, 
        validOptionNames = new string[] {"fn"}, 
        validOptionValue = new string[] { "File name" })]
    public class EncodeCommand : ICommand
    {
        public void Execute(string[] args, KeyValuePair<string, string>[] options)
        {
            string assetFileName = options.Contains("fn") ? options.GetOptionValue("fn") : "Asset";
            string assetFile = $"{args[1]}/{assetFileName}.asset";

            var loadedFolder = new AssetsBundle(AssetsBundle.GetFolder(args[0], true));
            byte[] serialized = MessagePackSerializer.Serialize(loadedFolder, ContractlessStandardResolver.Options);
            File.WriteAllBytes(assetFile, Utils.Compress(serialized));
            Console.WriteLine($"Successfully created and compressed \"{args[0]}\" in to \"{assetFile}\"");
        }
    }
}
