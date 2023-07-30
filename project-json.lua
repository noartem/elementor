import("core.base.json")
import("core.base.option")
import("core.project.config")
import("core.project.project")
import("core.platform.platform")

function main()
    local result = {}

    result["modes"] = project.modes()
    result["arch"] = config.get("arch") or os.arch()
    result["plat"] = config.get("plat") or os.host()
    result["mode"] = config.get("mode") or "release"

    local targetsResult = {}
    for target_name, target in pairs(project.targets()) do
        local targetResult = {}
        targetResult["name"] = target_name
        targetResult["kind"] = target:get("kind")
        targetResult["targetfile"] = target:targetfile()
        table.insert(targetsResult, targetResult)
    end
    result["targets"] = targetsResult

    local packages = project.required_packages()
    local packagesResult = {}
    for package_name, package in pairs(packages) do
        local packageResult = {}
        packageResult["name"] = package_name
        packageResult["includedirs"] = package:get("sysincludedirs")
        packageResult["linkdirs"] = package:get("linkdirs")
        packageResult["libfiles"] = package:get("libfiles")
        packageResult["bin"] = package:get("envs")["PATH"]
        packageResult["syslinks"] = package:get("syslinks")
        packageResult["links"] = package:get("links")
        table.insert(packagesResult, packageResult)
    end
    result["packages"] = packagesResult

    print(json.encode(result))
end
