# Elementor

## FAQ

### Build tool

[XMake](https://xmake.io)

### How to build project?

`$ xmake`

### How to configure project?

`$ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]`

### How to run and debug target after building project?

`$ xmake run [targetname]`
`$ xmake run -d [targetname]`

### How to install target to the system directory or other output directory?

`$ xmake install`
`$ xmake install -o installdir`

### Add some frequently-used compilation flags in xmake.lua

```lua
-- add debug and release modes
add_rules("mode.debug", "mode.release")

-- add macro defination
add_defines("NDEBUG", "_GNU_SOURCE=1")

-- set warning all as error
set_warnings("all", "error")

-- set language: c99, c++11
set_languages("c99", "c++11")

-- set optimization: none, faster, fastest, smallest
set_optimize("fastest")

-- add include search directories
add_includedirs("/usr/include", "/usr/local/include")

-- add link libraries and search directories
add_links("tbox")
add_linkdirs("/usr/local/lib", "/usr/lib")

-- add system link libraries
add_syslinks("z", "pthread")

-- add compilation and link flags
add_cxflags("-stdnolib", "-fno-strict-aliasing")
add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
```