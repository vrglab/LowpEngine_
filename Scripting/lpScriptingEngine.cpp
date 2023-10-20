#include "lpscpch.h"
#include "lpScriptingEngine.h"

LP_Export MonoAssembly* LoadCSharpAssembly(const std::string& assemblyPath)
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

LP_Export int InitScriptingEngine(std::string GameName, ScriptingEngine* engine)
{
    std::string monoPath;
    monoPath.append(std::filesystem::current_path().string());
    monoPath.append("\\Runtime\\Mono");
    mono_set_assemblies_path(monoPath.c_str());
    engine->root_domain = mono_jit_init("LowpEngineJITRuntime");
    if(engine->root_domain == nullptr)
    {
        return LowpResultCodes::SystemFailure;
    }

    engine->app_domain = mono_domain_create_appdomain((char*)GameName.c_str(), nullptr);
    if (engine->app_domain == nullptr)
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
    
    engine->core_assembly = LoadCSharpAssembly(coreAssembly);
    if (engine->core_assembly == nullptr)
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
   
    engine->game_assembly = LoadCSharpAssembly(gameAssembly);
    if (engine->game_assembly == nullptr)
    {
        return LowpResultCodes::SystemFailure;
    }

    return LowpResultCodes::Success;
}
