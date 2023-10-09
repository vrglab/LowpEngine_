using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LowpEngine.AssetManagement.Importer
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ImporterAttribute : Attribute
    {
        public List<string> FileExtension { get; } =  new List<string>();

        public ImporterAttribute(string fileExtension)
        {
            FileExtension.Add(fileExtension);
        }

        public ImporterAttribute(params string[] extensions)
        {
            foreach (var extension in extensions)
            {
                FileExtension.Add(extension);
            }
        }
    }
}
