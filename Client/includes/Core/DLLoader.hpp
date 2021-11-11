/*
** EPITECH PROJECT, 2020
** rtype_2020
** File description:
** DLLoader.hpp
*/

#ifndef _DYNLOADER_
#define _DYNLOADER_

#include <dlfcn.h>
#include <string>
#include <vector>

typedef unsigned int uint;

template <typename T>
class DLLoader {
public:
    DLLoader() = default;
    virtual ~DLLoader() {unload();};
public:
    void unload() {
        for (uint i = 0; i < handle.size(); i++)
            if (handle[i])
                dlclose(handle[i]);
    };
    void load(const std::string &str) {
        libPath = str;
        handle.push_back(dlopen(libPath.c_str(), RTLD_GLOBAL | RTLD_LAZY));
        if (handle[handle.size()-1] == NULL) {
            printf("%s\n", dlerror());
            throw std::invalid_argument("Lib doesn't exist");
        }
    }
    T *getInstance(std::string lib_name) {
        T *tmp;
        char *str;

        *(void **)(&fctPtr) = dlsym(handle[handle.size()-1], lib_name.c_str());
        if ((str = dlerror()) != NULL)
            throw std::runtime_error(dlerror());
        return fctPtr();
    };
    T *getInstance(std::string lib_name, IGraphic *a) {
        T *tmp;
        char *str;

        *(void **)(&fctPtrL) = dlsym(handle[handle.size()-1], lib_name.c_str());
        if ((str = dlerror()) != NULL)
            throw std::runtime_error(dlerror());
        return fctPtrL(a);
    };
public:
    std::vector<void *> handle;
    T *(*fctPtr)(void);
    T *(*fctPtrL)(IGraphic *);
    std::string libPath;
};

/*
template <typename T>
class DLLoader {
public:
    DLLoader() = default;
    virtual ~DLLoader() {unload();};
public:
    void unload() {
        if (handle)
            dlclose(handle);
    };
    void load(const std::string &str) {
        libPath = str;
        unload();
        void *ptr = dlopen(libPath.c_str(), RTLD_GLOBAL | RTLD_LAZY);
        if (ptr == NULL) {
            printf("%s\n", dlerror());
            throw std::invalid_argument("Lib doesn't exist");
        } 
        handle.push_back(ptr);
    }
    template<typename U>
    U *getInstance(const std::string &lib_name) {
        U *tmp;
        tmp = dlsym(handle[handle.size()-1], lib_name.c_str());
        if (tmp == NULL)
            throw std::runtime_error(dlerror());
        return tmp;
    };
    T *getInstanceGame(const std::string &lib_name) {
        T *(*fctPtr)(void);


        fctPtr = getInstance<void *()>(lib_name);
        return fctPtr();
    };
    T *getInstanceGraph(const std::string &lib_name, IGraphic *a) {
        T *(*fctPtrL)(Igraph *);

        fctPtrL = getInstance<void *(Igraph *)>(lib_name);
        return fctPtrL(a);
    };
public:
    void * handle;
    std::string libPath;
};*/

#endif