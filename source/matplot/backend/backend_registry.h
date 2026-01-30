//
// Created by Alan Freitas on 26/08/20.
//

#ifndef MATPLOTPLUSPLUS_BACKEND_REGISTRY_H
#define MATPLOTPLUSPLUS_BACKEND_REGISTRY_H

#include <matplot/detail/config.h>
#include <matplot/backend/backend_interface.h>
#include <matplot/backend/gnuplot.h>
#include <stdexcept>

namespace matplot {

    template <class BACKEND_TYPE, class ... Args>
    std::shared_ptr<backend::backend_interface> create_backend(Args&&... args) {
        if (std::is_base_of<backend::backend_interface, BACKEND_TYPE>::value)
        {
            std::shared_ptr<BACKEND_TYPE> dp = std::make_shared<BACKEND_TYPE>(std::forward<Args>(args)...);
            std::shared_ptr<backend::backend_interface> bp =
                std::dynamic_pointer_cast<backend::backend_interface>(dp);
            return bp;
        } else {
            throw std::invalid_argument(
                std::string("The class ") + typeid(BACKEND_TYPE).name() +
                " does not derive from backend::backend_interface");
        }
    }

    typedef backend::backend_interface* (*create_backend_func)();

    MATPLOT_EXPORTS
    std::shared_ptr<backend::backend_interface> create_default_backend();

    MATPLOT_EXPORTS
    void register_backend(const std::string& name, create_backend_func func);

    MATPLOT_EXPORTS
    void change_default_backend(const std::string& name);

    MATPLOT_EXPORTS
    void change_default_backend(create_backend_func func);

    MATPLOT_EXPORTS
    std::shared_ptr<backend::backend_interface> create_backend(const std::string& name);


} // namespace matplot

#endif // MATPLOTPLUSPLUS_BACKEND_REGISTRY_H
