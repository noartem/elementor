package("skia-build")
    set_homepage("https://github.com/noartem/skia-build")
    set_description("Automated Skia builds")

    if is_host("windows") then
	    if os.arch() == "x64" then
            add_urls("https://github.com/noartem/skia-build/releases/download/m102-32283b3f00/Skia-m102-32283b3f00-windows-Release-x64.zip")
            add_versions("102", "46e511e3b22c6698b5f1d68cc2b607e6f43f9919a702f791100347831e8ce953")
        end
    elseif is_host("linux") then
        if os.arch() == "x86_64" then
            add_urls("https://github.com/noartem/skia-build/releases/download/m102-32283b3f00/Skia-m102-32283b3f00-linux-Release-x64.zip")
            add_versions("102", "d3ab60a9bf01046c3b837df7bc4394511ded28c9d94816905bd9e7f6ec5159fa")
        end
    elseif is_host("macosx") then
        if os.arch() == "arm64" then
            add_urls("https://github.com/noartem/skia-build/releases/download/m102-32283b3f00/Skia-m102-32283b3f00-macos-Release-arm64.zip")
            add_versions("102", "46e511e3b22c6698b5f1d68cc2b607e6f43f9919a702f791100347831e8ce953")
        else
            add_urls("https://github.com/noartem/skia-build/releases/download/m102-32283b3f00/Skia-m102-32283b3f00-macos-Release-x64.zip")
            add_versions("102", "46e511e3b22c6698b5f1d68cc2b607e6f43f9919a702f791100347831e8ce953")
        end
    end

    add_includedirs("")
    add_links("skottie", "svg", "skparagraph", "skshaper", "skunicode", "dng_sdk", "skia", "sksg",
              "skresources", "z", "tinfo", "ncurses", "freetype", "fontconfig", "webp_sse41", "jpeg",
              "harfbuzz", "particles", "zlib", "icu", "png", "expat", "piex", "webp")
    if is_plat("windows") then
        add_syslinks("gdi32", "user32", "opengl32", "d3d12", "d3dcompiler", "dxgi", "dxguid")
    elseif is_plat("macosx") then
        add_frameworks("CoreFoundation", "CoreGraphics", "CoreText", "CoreServices")
    elseif is_plat("linux") then
        add_deps("fontconfig", "freetype >=2.10")
        add_syslinks("pthread", "GL", "dl", "rt")
    end

    on_install("macosx", "linux", "windows", function (package)
        if os.arch() == "arm64" then
            os.mv("out/Release-arm64/*", package:installdir("lib"))
        else
            os.mv("out/Release-x64/*", package:installdir("lib"))
        end
        os.rm("out")

        os.cp("*", package:installdir())
    end)

    on_test(function (package)
        assert(package:check_cxxsnippets({test = [[
            void test() {
                SkPaint paint;
                paint.setStyle(SkPaint::kFill_Style);
            }
        ]]}, {configs = {languages = "c++17"}, includes = "include/core/SkPaint.h"}))
    end)
package_end()
