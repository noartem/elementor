package("skia-build")
    set_homepage("https://github.com/noartem/skia-build")
    set_description("Automated Skia builds")

    local codes = {["102"] = "m102-32283b3f00",
                   ["105"] = "m105-f204b137b9"}

    if is_host("windows") then
	    if os.arch() == "x64" then
            add_urls("https://github.com/noartem/skia-build/releases/download/$(version)/Skia-$(version)-windows-Release-x64.zip",
            {version = function (version) return codes[tostring(version)] end})
            add_versions("102", "df2370473e0ed690f83ca056611c0c43346cad23ca76c61c82d70de44e862818")
            add_versions("105", "e2e07304ff2f735dc0ef50c60ac22fb3259df4b1bb7e4a21e00de08f47d464a9")
        end
    elseif is_host("linux") then
        if os.arch() == "x86_64" then
            add_urls("https://github.com/noartem/skia-build/releases/download/$(version)/Skia-$(version)-linux-Release-x64.zip",
                     {version = function (version) return codes[tostring(version)] end})
            add_versions("102", "782b13ac32f2c391566f5a991ce3fc090f312e4a1a61c2d90d74f6b220f510b3")
            add_versions("105", "faea9844cfc43e826171e67c5f7c51faef0eee47af6f06a4fb25a0ea377daf8e")
        end
    elseif is_host("macosx") then
        if os.arch() == "arm64" then
            add_urls("https://github.com/noartem/skia-build/releases/download/$(version)/Skia-$(version)-macos-Release-arm64.zip",
                     {version = function (version) return codes[tostring(version)] end})
            add_versions("102", "c5d6e555e52a8d0509320152ad63bfb34fb12905187df7a6c9482cb2de14c7d4")
            add_versions("105", "9f6fdb223b16e9d83d3ac3f2b810bc93ee04983fa3635caec5aead9658d6234b")
        else
            add_urls("https://github.com/noartem/skia-build/releases/download/$(version)/Skia-$(version)-macos-Release-x64.zip",
                     {version = function (version) return codes[tostring(version)] end})
            add_versions("102", "4c30353ca0467bf1680352ee99062dfc13af39c600c94cb0572cf4284f35ef02")
            add_versions("105", "4ded987a413a6fc58c318c4ace862a4f25ca4d7f826edc83f3659940f7076211")
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
