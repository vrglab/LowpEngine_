sh Programs\vcpkg\bootstrap-vcpkg.sh
chmod +x "Programs/Linux/premake/premake5"
"Programs/Linux/premake/premake5" gmake2
"Programs\vcpkg\vcpkg" integrate install

