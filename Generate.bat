set "VCPKG_ROOT=Programs\Windows\LowpPackages"
set "set VCPKG_TARGET_TRIPLET=auto"
Programs\Windows\LowpPackages\LowpPackages.exe clean-install packages.xml
Programs\Windows\premake\premake5.exe vs2022