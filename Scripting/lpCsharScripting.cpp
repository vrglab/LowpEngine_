#include "lpscpch.h"
#include "lpCsharScripting.h"

LP_Export Assembly* LoadAssembly()
{
    Assembly* assembly = new Assembly();
    assembly->domain = mono_jit_init("LowpEngine");
    assembly->assembly = mono_domain_assembly_open(assembly->domain, "Assembly.dll");
    if (assembly) {
        assembly->image = mono_assembly_get_image(assembly->assembly);
        mono_jit_exec(assembly->domain, assembly->assembly, 0, NULL);
    }
    return assembly;
}

LP_Export void InitializeAssembly(Assembly* assembly)
{
    
}

LP_Export void CleanAssembly(Assembly* assembly)
{
    delete assembly;
}
