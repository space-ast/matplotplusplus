//
// Created by Alan Freitas on 26/08/20.
//

#include "backend_registry.h"
#include <map>

namespace matplot {
    
    static backend::backend_interface* create_gnuplot_backend()
    {
        #if defined __wasm__
        return nullptr;
        #else
        return new backend::gnuplot();
        #endif
    }

    static std::map<std::string, create_backend_func> s_backend_factory{
        {"gnuplot", &create_gnuplot_backend}
    };
    
    static create_backend_func s_default_backend_factory = &create_gnuplot_backend;

    std::shared_ptr<backend::backend_interface> create_default_backend() {

        return std::shared_ptr<backend::backend_interface>(s_default_backend_factory());
    }
    void register_backend(const std::string& name, create_backend_func func)
    {
        if (!func)
            return;
        s_backend_factory.insert({name, func});
    }
    void change_default_backend(const std::string& name)
    {
        auto iter = s_backend_factory.find(name);
        if (iter != s_backend_factory.end())
        {
            s_default_backend_factory = iter->second;
        }
    }
    void change_default_backend(create_backend_func func)
    {
        if (!func)
            return;
        s_default_backend_factory = func;
    }
    std::shared_ptr<backend::backend_interface> create_backend(const std::string& name)
    {
        auto iter = s_backend_factory.find(name);
        if (iter != s_backend_factory.end())
        {
            return std::shared_ptr<backend::backend_interface>(iter->second());
        }
        return std::shared_ptr<backend::backend_interface>();
    }
    } // namespace matplot