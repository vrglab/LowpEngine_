#include "lpscpch.h";
#include "lpScriptingEngine.h"

MonoObject* MonoBehaviourChild::CreateInstance(ScriptingEngine* engine)
{
	MonoObject* object = mono_object_new(engine->root_domain, classType);
	mono_runtime_object_init(object);
	mono_runtime_invoke(awakeMethod, nullptr, nullptr, &object);
	return object;
}