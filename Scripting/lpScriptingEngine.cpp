#include "lpscpch.h"
#include "lpScriptingEngine.h"
#include <SceneEngine/lpSceneEngine.h>

LP_Export MonoAssembly* ScriptingEngine::LoadCSharpAssembly(const std::string& assemblyPath)
{
    uint32_t fileSize = 0;
    char* fileData = ReadBytes(assemblyPath, &fileSize);

    // NOTE: We can't use this image for anything other than loading the assembly because this image doesn't have a reference to the assembly
    MonoImageOpenStatus status;
    MonoImage* image = mono_image_open_from_data_full(fileData, fileSize, 1, &status, 0);

    if (status != MONO_IMAGE_OK)
    {
        const char* errorMessage = mono_image_strerror(status);
        // Log some error message using the errorMessage data
        return nullptr;
    }

    MonoAssembly* assembly = mono_assembly_load_from_full(image, assemblyPath.c_str(), &status, 0);
    mono_image_close(image);

    // Don't forget to free the file data
    delete[] fileData;

    return assembly;
}

LP_Export int ScriptingEngine::Init(std::string GameName)
{
    std::string monoPath;
    monoPath.append(std::filesystem::current_path().string());
    monoPath.append("\\Runtime\\Mono");
    mono_set_assemblies_path(monoPath.c_str());
    root_domain = mono_jit_init("LowpEngineJITRuntime");
    if(root_domain == nullptr)
    {
        return LowpResultCodes::SystemFailure;
    }

    app_domain = mono_domain_create_appdomain((char*)GameName.c_str(), nullptr);
    if (app_domain == nullptr)
    {
        return LowpResultCodes::SystemFailure;
    }

    std::string coreAssembly;
    coreAssembly.append(std::filesystem::current_path().string());
    coreAssembly.append("\\Runtime\\");
#ifdef _WIN32
    coreAssembly.append("LowpEngine.dll");
#endif
#ifdef __linux__
    coreAssembly.append("LowpEngine.so");
#endif
#ifdef __APPLE__
    coreAssembly.append("LowpEngine.dylib");
#endif
    
    core_assembly = LoadCSharpAssembly(coreAssembly);
    if (core_assembly == nullptr)
    {
        return LowpResultCodes::SystemFailure;
    }

    std::string gameAssembly;
    gameAssembly.append(std::filesystem::current_path().string());
    gameAssembly.append("\\Runtime\\");
    gameAssembly.append(GameName);
#ifdef _WIN32
    gameAssembly.append(".dll");
#endif
#ifdef __linux__
    gameAssembly.append(".so");
#endif
#ifdef __APPLE__
    gameAssembly.append(".dylib");
#endif
   
    game_assembly = LoadCSharpAssembly(gameAssembly);
    if (game_assembly == nullptr)
    {
        return LowpResultCodes::SystemFailure;
    }

    return LowpResultCodes::Success;
}


LP_Export void ScriptingEngine::Update()
{
    if (activeScene != nullptr)
    {
        for (auto behaviour : activeScene->created_objects)
        {
            mono_runtime_invoke(behaviour.first->updateMethod, nullptr, nullptr, &behaviour.second);
        }
    }
}

LP_Export void ScriptingEngine::Cleanup()
{
    mono_assemblies_cleanup();
    mono_jit_cleanup(app_domain);
    mono_jit_cleanup(root_domain);
}
