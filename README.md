# LowpEngine
C++/C# based Game Engine, fully free and open source.

# Important
I should mention certain project's such as the ConsoleAppEngine and GlobalUtilities projects are standalone projects than can be used in other things without the direct need of the Entire Engine. 
## list of Projects

1. Engine (C++ Core): This is the core engine.
1. PhysicsEngine (C++): The Physics engine, uses both ODE and Box2D to handle diffrent Physics contexts
1. RenderingEngine (C++): The our own cross-platform Rendering Engine 
1. SoundSystem (C++): The Engine in charge of handling audio systems (Multibackend: OpenAL, Fmod ...)
1. Scripting (C++): The main engine handeling C# scripting
1. EngineCommons (C++): All of the code shared between diffrent (C++) projects.
9. Launcher(C++): The main launcher. (the executable to launch the game basically)
1. AssetSystem(C#): Is a C# based engine that handles the games assets
2. AssetsTool(C#): A tool for generating Asset bundles and turning asset bundles into their original form
3. ConsoleAppEngine(C#): A Engine for making Cosnole application (executing commands, reading command options, loading custom commands to be executed ...)
7. GlobalUtilities(C#): All of the code shared between diffrent (C#) projects.
8. LowpEngine (C#): The Core's C# modul. (used for scripting)
1. TestGame(C#): The C# scripting test.


# Building/IDE Envoirment Generation
Clone the project using `git clone git@github.com:vrglab/LowpEngine.git` and Run the `Generate` this should generate the default IDE envoirment after that you need to run the `InstallPackages` file for your os

### Windows
On windows running the `Generate.bat` file should by default create `Visual Studio Comunity 2022` project files and using Viisual Studio you should be able to just build the project.

### Linux
On linux running the `Generate.sh` file in the console using `sh`,should by default create `Gmake2` files and by running the `make` command in the bash you should be able to build the project

# Currently Supported features
This are all of the feature that are already fully or partially implemented into the Project
1. OpenGl, Vulkan, DirectX11, Metal.
1. Bash based executables.
1. Asset Controll.
1. Customizable Asset importer.

# Planned to Support
this are all feature i plan on supporting (that i can remember right now)
1. 2D/3D.
1. Engine Customization.
1. Game object/Component system.
1. Built in Audio system (OpenAL, Fmod, Wwise).
1. 3D model loading.
1. Physics 2D/3D.
1. Particles.
2. Indexed Rendering.
3. Mesh batching.
4. Builtin base components.
4. Multiplatform building (Consoles, Phones, Computers).
