import("core.base.global")

function main()
    os.rm("build")
    os.rm(".xmake")
    os.rm("CMakelists.txt")

--     os.rm(global.directory())

    os.rm(path.join("src", "napi", "binding.gyp"))
    os.rm(path.join("src", "napi", "node_modules"))
    os.rm(path.join("src", "napi", "build"))
    os.rm(path.join("src", "napi", "dist"))
end
