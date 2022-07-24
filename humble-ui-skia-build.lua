package("skia-build")
    set_homepage("https://github.com/HumbleUI/SkiaBuild")
    set_description("Automated Skia builds")

    if is_host("windows") then
        if os.arch() == "x64" then
            add_urls("https://github.com/HumbleUI/SkiaBuild/releases/download/m102-32283b3f00/Skia-m102-32283b3f00-windows-Release-x64.zip")
            add_versions("102", "d07fcb40340699fcba08e353367235b439f5e43552782996f85c7d4eb0748bab")
        end
    elseif is_host("linux") then
        if os.arch() == "x86_64" then
            add_urls("https://github.com/HumbleUI/SkiaBuild/releases/download/m102-32283b3f00/Skia-m102-32283b3f00-linux-Release-x64.zip")
            add_versions("102", "2491d52a7839ed970d0cfa69566fb6b9595671e8803e3675163e0d674771df80")
        end
    elseif is_host("macosx") then
        if os.arch() == "arm64" then
            add_urls("https://github.com/HumbleUI/SkiaBuild/releases/download/m102-32283b3f00/Skia-m102-32283b3f00-macos-Release-arm64.zip")
            add_versions("102", "aed98380a5bbe1becd803cd1cc5af48fef2a674dc0c4e3a74d912c066d454997")
        else
            add_urls("https://github.com/HumbleUI/SkiaBuild/releases/download/m102-32283b3f00/Skia-m102-32283b3f00-macos-Release-x64.zip")
            add_versions("102", "ae61e08113e4e51c4889741e9fd110e3c8885dd171bc5b52fbbb1869e2b0d547")
        end
    end

    add_includedirs("")
    if is_plat("windows") then
        add_syslinks("gdi32", "user32", "opengl32")
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