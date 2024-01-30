add_rules("mode.debug", "mode.release")

set_languages("c99", "cxx23")

includes("third_party/skia-build.lua")
includes("third_party/portable-file-dialogs.lua")

add_requires("skia-build")
add_requires("glfw 3.3.8")
add_requires("doctest")
add_requires("tl_expected")
add_requires("fastcppcsvparser")
add_requires("portable-file-dialogs")

if is_plat("windows") then
    add_requires("glew")
end

if is_mode("debug") then
    add_defines("DEBUG")
end

if is_plat("windows") then
    add_defines("OS_HOST_WINDOWS")
elseif is_plat("linux") then
    add_defines("OS_HOST_LINUX")
elseif is_plat("macosx") then
    add_defines("OS_HOST_MACOS")
end

target("elementor")
    set_kind("static")
    add_packages("skia-build", "glfw")
    add_files("src/library/*.cpp")
    add_files("src/library/platforms/*/*.cpp")
    add_files("src/library/elements/*.cpp")
    add_cxxflags('-fPIC')

if is_plat("windows") then
    add_packages("glew")

    after_build(function (target)
        local project = target._PROJECT
        local skiaBuild = project.required_packages()['skia-build']
        os.cp(
            path.join(skiaBuild:get('linkdirs'), "icudtl.dat"),
            path.join(project.directory(), "build", "$(plat)", "$(arch)", "$(mode)", "icudtl.dat")
        )
    end)
end

target("elementor-components")
    set_kind("static")
    add_deps("elementor")
    add_packages("skia-build", "glfw")
    add_files("src/components/*.cpp")

target("example")
    set_kind("binary")
    add_deps("elementor", "elementor-components")
    add_packages("skia-build", "glfw")
    add_files("src/example/*.cpp")
