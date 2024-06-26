add_rules("mode.debug", "mode.release")

set_languages("c99", "cxx23")

includes("third_party/skia-build.lua")
add_requires("skia-build")

add_requires("glfw 3.3.8")
if is_plat("windows") then
    add_requires("glew")
end

if is_mode("debug") then
    add_defines("DEBUG")
--     set_policy("build.sanitizer.address")
    set_policy('build.sanitizer.undefined')
    set_policy('build.sanitizer.leak')
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
    add_packages("skia-build")
    add_files("src/library/*.cpp")
    add_files("src/library/elements/*.cpp")

-- if is_plat("windows") then
--     after_build(function (target)
--         local project = target._PROJECT
--         local skiaBuild = project.required_packages()['skia-build']
--         os.cp(
--             path.join(skiaBuild:get('linkdirs'), "icudtl.dat"),
--             path.join(project.directory(), "build", "$(plat)", "$(arch)", "$(mode)", "icudtl.dat")
--         )
--     end)
-- end

target("elementor-components")
    set_kind("static")
    add_deps("elementor")
    add_packages("skia-build")
    add_files("src/components/*.cpp")

target("elementor-glfw")
    set_kind("static")
    add_packages("skia-build", "glfw")
    add_files("src/library/platforms/*/*.cpp")
if is_plat("windows") then
    add_packages("glew")
end

target("example-basic")
    set_kind("binary")
    add_deps("elementor", "elementor-components", "elementor-glfw")
    add_packages("skia-build", "glfw")
    add_files("src/examples/basic/*.cpp")

target("example-button")
    set_kind("binary")
    add_deps("elementor", "elementor-components", "elementor-glfw")
    add_packages("skia-build", "glfw")
    add_files("src/examples/button/*.cpp")

target("example-counter")
    set_kind("binary")
    add_deps("elementor", "elementor-components", "elementor-glfw")
    add_packages("skia-build", "glfw")
    add_files("src/examples/counter/*.cpp")

target("example-crud")
    set_kind("binary")
    add_deps("elementor", "elementor-components", "elementor-glfw")
    add_packages("skia-build", "glfw")
    add_files("src/examples/crud/*.cpp")

target("example-flex")
    set_kind("binary")
    add_deps("elementor", "elementor-components", "elementor-glfw")
    add_packages("skia-build", "glfw")
    add_files("src/examples/flex/*.cpp")

target("example-tempconv")
    set_kind("binary")
    add_deps("elementor", "elementor-components", "elementor-glfw")
    add_packages("skia-build", "glfw")
    add_files("src/examples/tempconv/*.cpp")

target("example-text")
    set_kind("binary")
    add_deps("elementor", "elementor-components", "elementor-glfw")
    add_packages("skia-build", "glfw")
    add_files("src/examples/text/*.cpp")

target("example-todo")
    set_kind("binary")
    add_deps("elementor", "elementor-components", "elementor-glfw")
    add_packages("skia-build", "glfw")
    add_files("src/examples/todo/*.cpp")

target("examples")
    set_kind("binary")
    add_deps("elementor", "elementor-components", "elementor-glfw")
    add_packages("skia-build", "glfw")
    add_files("src/examples/*.cpp")

target("make-screenshots")
    set_kind("binary")
    add_deps("elementor", "elementor-components", "elementor-glfw")
    add_packages("skia-build", "glfw")
    add_files("tests/make_screenshots.cpp")
