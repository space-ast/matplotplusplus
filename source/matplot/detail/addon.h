#pragma once
#include <matplot/detail/string_view.h>

#if __cplusplus >= 201703L
#   define MATPLOT_NODISCARD [[nodiscard]]
#else
#   define MATPLOT_NODISCARD
#endif

namespace matplot {
       template <typename T>
    inline T clamp(T val, T vmin, T vmax)
    {
        if (val < vmin)
            return vmin;
        if (val > vmax)
            return vmax;
        return val;
    }
} // namespace matplot