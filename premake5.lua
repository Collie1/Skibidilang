-- premake5.lua
workspace "SkibidiLang"
    configurations { "Release" }


    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    include "SkibidiLang"