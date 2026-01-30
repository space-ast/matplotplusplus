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
        