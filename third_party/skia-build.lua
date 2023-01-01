package("skia-build")
    set_homepage("https://github.com/noartem/skia-build")
    set_description("Automated Skia builds")

    local codes = {["102"] = "m102-32283b3f00",
                   ["105"] = "m105-f204b137b9",
                   ["109"] = "m109-664500fa93"}

    if is_host("windows") then
	    if os.arch() == "x64" then
            add_urls("https://github.com/noartem/skia-build/releases/download/$(version)/Skia-$(version)-windows-Release-x64.zip",
            {version = function (version) return codes[tostring(version)] end})
            add_versions("102", "df2370473e0ed690f83ca056611c0c43346cad23ca76c61c82d70de44e862818")
            add_versions("105", "6694eb8346e0e9e51976425755aa2fbd1ddaf92bf1417dbcebbdd54ba20a6337")
            add_versions("109", "5d6367c1f967478d8da6f55edc1653e63ac1c93261bc519e04083e8a46a6078e")
        end
    elseif is_host("linux") then
        if os.arch() == "x86_64" then
            add_urls("https://github.com/noartem/skia-build/releases/download/$(version)/Skia-$(version)-linux-Release-x64.zip",
                     {version = function (version) return codes[tostring(version)] end})
            add_versions("102", "782b13ac32f2c391566f5a991ce3fc090f312e4a1a61c2d90d74f6b220f510b3")
            add_versions("105", "48293711d2477fb2fafeaba1e1a67d0277b27d877ba92d5c0a08e4aaf8eb85d3")
            add_versions("109", "d1965ed195d3cef298ce30c6fed6b5a5658a229a1fa863d6019fe9169aee459f")
        end
    elseif is_host("macosx") then
        if os.arch() == "arm64" then
            add_urls("https://github.com/noartem/skia-build/releases/download/$(version)/Skia-$(version)-macos-Release-arm64.zip",
                     {version = function (version) return codes[tostring(version)] end})
            add_versions("102", "c5d6e555e52a8d0509320152ad63bfb34fb12905187df7a6c9482cb2de14c7d4")
            add_versions("105", "6cfde3a6dcee59b6830f346f5b550abca13c4be5c643603f2dd17ea1c74f88e7")
            add_versions("109", "8abd9284b3ee9d4557103421689f4dda5b81e11380818a7676cdb6fa82efff87")
        else
            add_urls("https://github.com/noartem/skia-build/releases/download/$(version)/Skia-$(version)-macos-Release-x64.zip",
                     {version = function (version) return codes[tostring(version)] end})
            add_versions("102", "4c30353ca0467bf1680352ee99062dfc13af39c600c94cb0572cf4284f35ef02")
            add_versions("105", "1e353994d02f7b71e912c3139aa22fdac19a165d780dc268e6e79b1a08ee0a6d")
            add_versions("109", "df2ecdc74bd93121597d658f5e512206479e0ae2d9ed0696b6374232d40227d9")
        end
    end

    add_includedirs("")
    add_links("skottie", "svg", "skparagraph", "skshaper", "skunicode", "dng_sdk", "skia", "sksg",
              "skresources", "z", "tinfo", "ncurses", "freetype", "fontconfig", "webp_sse41", "jpeg",
              "harfbuzz", "particles", "zlib", "icu", "png", "expat", "piex", "webp")
    if is_plat("windows") then
        add_syslinks("advapi32", "gdi32", "user32", "opengl32", "d3d12", "d3dcompiler", "dxgi", "dxguid")
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
