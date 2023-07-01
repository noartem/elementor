import("core.base.option")
import("core.project.config")
import("core.project.project")
import("core.platform.platform")

local function isDictionary(value)
    for k, v in pairs(value) do
        if type(k) ~= "number" then
            return true
        end
    end
    return false
end

local function convertTableToJSON(tbl)
    local result = {}

    local is_dictionary = isDictionary(tbl)

    for key, value in pairs(tbl) do
        if type(value) == "table" then
            value = convertTableToJSON(value)
        elseif type(value) == "string" then
            value = "\"" .. string.gsub(string.gsub(value, "\"", "\\\""), "\\", "\\\\") .. "\""
        end

        if is_dictionary then
            table.insert(result, string.format("\"%s\":%s", key, value))
        else
            table.insert(result, value)
        end
    end

    if is_dictionary then
        return "{" .. table.concat(result, ",") .. "}"
    else
        return "[" .. table.concat(result, ",") .. "]"
    end
end

function main()
    local result = {}

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
        table.insert(packagesResult, packageResult)
    end
    result["packages"] = packagesResult

    print(convertTableToJSON(result))
end
