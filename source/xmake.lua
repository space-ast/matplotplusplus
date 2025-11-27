target("matplot")
    set_kind("shared")

    add_files("**.cpp")

    remove_files("matplot/backend/opengl*.cpp")
    remove_files("matplot/util/world_*.cpp")

    add_defines("MATPLOT_BUILT")
    add_defines("_USE_MATH_DEFINES")
    add_defines("NOMINMAX")
    add_defines("STRING_VIEW_CONSTEXPR_BUG")
    add_defines("CXX_NO_FILESYSTEM")

    if is_plat("windows") then
        add_syslinks("user32", "gdi32", "shell32")
    end
    
    add_includedirs(".", {public=true})
    add_includedirs("3rd_party/nodesoup/include")
    add_includedirs("3rd_party/cimg")

    before_build(function (target)
        local dirpath = path.join(os.scriptdir(), "matplot", "detail")
        os.mkdir(dirpath)
        local filepath = path.join(dirpath, "config.h")
        if os.exists(filepath) then
            return
        end
        io.writefile(filepath, [[
#pragma once
#include <matplot/detail/addon.h>
#ifdef _WIN32
#   ifdef MATPLOT_BUILT    
#       define MATPLOT_EXPORTS __declspec(dllexport)
#   else
#       define MATPLOT_EXPORTS __declspec(dllimport)
#   endif
#else
#       define MATPLOT_EXPORTS __attribute__((visibility("default")))
#endif
        ]]
        )

    end)
