import("core.base.option")
import("core.project.config")
import("core.project.project")
import("core.platform.platform")

function main()
    local includeDirs = {}
    local links = {}

    --print(project.required_packages())
    local target = project.targets()['elementor']
    for _, package_name in ipairs(target:get("packages")) do
        local package = project.required_packages()[package_name]
        table.insert(includeDirs, package:installdir("include"))

        for _, link in ipairs(package:get("links")) do
            table.insert(links, link)
        end
    end

    local result = {}
    result["include_dirs"] = includeDirs
    result["links"] = links

    print(result)
    --local packages = project.packages()
    --print(packages)
    --if #targetIncludeDirs > 0 then
    --    print("Target: " .. target:name())
    --    for _, includeDir in ipairs(targetIncludeDirs) do
    --        print("Include Directory: " .. includeDir)
    --    end
    --    print("----------------------------------------")
    --end
end
