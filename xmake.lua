add_rules("mode.debug", "mode.release")

set_languages("c99", "cxx17")

add_requires("skia")
add_requires("glfw")
add_requires("glew")
add_requires("doctest")

target("elementor")
    set_kind("static")
    add_packages("skia", "glfw", "glew")
    add_files("src/library/*.cpp")

target("elementor-test")
    set_kind("binary")
    add_packages("skia", "glfw")
    add_deps("elementor")
    add_files("src/*.cpp")

target("tests")
    set_kind("binary")
    add_packages("doctest")
    add_files("tests/*.cpp")
