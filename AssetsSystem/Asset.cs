using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AssetsSystem
{
    public class Asset
    {
        public DiskResource Resource { get; set; }
        public Type LoaderType { get; set; }
        public Dictionary<string, object> Properties { get; set; }
        public Guid Id { get; }

       
        public Asset(DiskResource resource, Type loaderType, Dictionary<string, object> properties, Guid id) 
        {
            Resource = resource;
            LoaderType = loaderType;
            Properties = properties;
            Id = id;
        }

        public Asset(DiskResource resource, Type loaderType, Dictionary<string, object> properties) : this(resource, loaderType, properties, Guid.NewGuid())
        {
            
        }
    }
}
