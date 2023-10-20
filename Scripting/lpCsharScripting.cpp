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

LP_Export int InitializeAssembly(Assembly* assembly)
{
    assembly->BehaviourRegistery = mono_class_from_name(assembly->image, "LowpEngine.Scripting", "BehaviourRegistery");
    if (assembly->BehaviourRegistery == nullptr) {
        return LowpResultCodes::SystemFailure;
    }
    
    MonoClassField* registeredBehavioursField = mono_class_get_field_from_name(assembly->BehaviourRegistery, "RegisteredBehaviours");
    MonoObject* scriptObjectsArray = mono_field_get_value_object(assembly->domain, registeredBehavioursField, NULL);
    MonoArray* scriptObjectsArrayUnboxed = (MonoArray*)mono_object_unbox(scriptObjectsArray);

    for (int i = 0; i < mono_array_length(scriptObjectsArrayUnboxed); i++) {
        MonoObject* scriptObject = mono_array_get(scriptObjectsArrayUnboxed, MonoObject*, i);
        MonoClass* monoBehvaiourClass = (MonoClass*)mono_object_unbox(scriptObject);
        CSharpMonoBehaviour* foundMonoBehvaiour = new CSharpMonoBehaviour();
        
        foundMonoBehvaiour->LoadedClass = scriptObject;
        foundMonoBehvaiour->Awake = mono_class_get_method_from_name(monoBehvaiourClass, "Awake", 0);
        foundMonoBehvaiour->Start = mono_class_get_method_from_name(monoBehvaiourClass, "Start", 0);
        foundMonoBehvaiour->Update = mono_class_get_method_from_name(monoBehvaiourClass, "Update", 0);
        foundMonoBehvaiour->OnEnable = mono_class_get_method_from_name(monoBehvaiourClass, "OnEnable", 0);
        foundMonoBehvaiour->OnDisable = mono_class_get_method_from_name(monoBehvaiourClass, "OnDisable", 0);
        foundMonoBehvaiour->OnDestroy = mono_class_get_method_from_name(monoBehvaiourClass, "OnDestroy", 0);
        assembly->behaviours->behaviours.push_back(foundMonoBehvaiour);
        delete monoBehvaiourClass;
    }
    delete scriptObjectsArrayUnboxed;
    delete scriptObjectsArray;
    delete registeredBehavioursField;
    return LowpResultCodes::Success;
}

LP_Export void CleanAssembly(Assembly* assembly)
{
    delete assembly;
}
