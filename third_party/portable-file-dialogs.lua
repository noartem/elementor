package("portable-file-dialogs")
    set_homepage("https://github.com/samhocevar/portable-file-dialogs")
    set_description("Portable GUI dialogs library, C++11, single-header")
    set_license("WTFPL")

    add_urls("https://github.com/samhocevar/portable-file-dialogs.git")
    add_versions("0.1.1", "5652fbd0df05f001aa2e92d86c22f762a03c1fd9")

    on_install(function (package)
        os.cp("portable-file-dialogs.h", package:installdir("include"))
    end)

    on_test(function (package)
        assert(package:check_cxxsnippets({test = [[
            void test(int argc, char** argv) {
                // File open
                auto f = pfd::open_file("Choose files to read", pfd::path::home(), { "Text Files (.txt .text)", "*.txt *.text", "All Files", "*" }, pfd::opt::multiselect);
                std::cout << "Selected files:";
                for (auto const &name : f.result())
                    std::cout << " " + name;
                std::cout << "\n";
            }
        ]]},{includes = "portable-file-dialogs.h", configs = {languages = "cxx11"}}))
    end)
package_end()