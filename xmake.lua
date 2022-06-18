add_rules("mode.debug", "mode.release")

set_languages("c99", "cxx17")

add_requires("skia")
add_requires("glfw")
add_requires("doctest")

if is_plat("windows") then
    add_requires("glew")
end

if is_mode("debug") then
    add_defines("DEBUG")
end

target("elementor")
    set_kind("static")
    add_packages("skia", "glfw", "glut")
    add_files("src/library/*.cpp")
    add_files("src/library/elements/*.cpp")

if is_plat("windows") then
    add_packages("glew")
end

target("examples")
    set_kind("binary")
    add_deps("elementor")
    add_packages("skia", "glfw")
    add_files("src/examples/*.cpp")

target("tests")
    set_kind("binary")
    add_packages("doctest")
    add_files("tests/*.cpp")
