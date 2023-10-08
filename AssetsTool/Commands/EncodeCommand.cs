using ConsoleAppEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AssetsTool.Commands
{
    [Command("encode", 2, "comp")]
    public class EncodeCommand : ICommand
    {
        public void Execute(string[] args, KeyValuePair<string, string>[] options)
        {
            bool Compress = options.Contains(new KeyValuePair<string, string>("comp", ""));

            if (Compress)
            {

            }
            else
            {

            }
        }
    }
}
