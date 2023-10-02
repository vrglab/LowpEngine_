#!/bin/bash

VCPKG_ROOT="Programs/Linux/LowpPackages"
VCPKG_TARGET_TRIPLET="auto"

"Programs/Linux/LowpPackages/LowpPackages.exe" clean-install packages.xml
"Programs/Linux/premake/premake" vs2022
