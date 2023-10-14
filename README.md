# LowpEngine
C++/C# based Game Engine, fully free and open source.

# Important
I should mention certain project's such as the ConsoleAppEngine and GlobalUtilities projects are standalone projects than can be used in other things without the direct need of the Entire Engine. 
## list of Projects and thier internal dependencies on eachother

1. AssetSystem: is Dependent only on number 7.
2. AssetsTool: is Dependent on numbers 1, 3, 7.
3. ConsoleAppEngine: is Dependent only on number 7.
4. Editor: is Dependent on numbers 1, 2, 7, 8.
5. Engine (C++ Core): No internal project Dependencies.
6. Engine.UI (c++ Engine UI lib): is Dependent only on number 5.
7. GlobalUtilities: No internal project Dependencies.
8. LowpEngine (C# bindings/implementation of Core Engine and Engine UI): is Dependent on numbers: 1, 5, 6, 7.
9. Launcher: is Dependent on numbers: 7 and 8.
1. TestGame: is Dependent only on number 8.
1. PhysicsEngine (C++): No internal project Dependencies.
1. RenderingEngine (C++): No internal project Dependencies.
1. SoundSystem (C++): No internal project Dependencies.



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
