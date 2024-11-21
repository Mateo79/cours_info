#include "singleton.h"

#include <stdlib.h>

Singleton* Singleton::_instance = nullptr;

Singleton::Singleton()
{
}

Singleton::~Singleton()
{
}

Singleton* Singleton::instance()
{
        // instance retardée
        if (_instance == nullptr) {
                _instance = new Singleton;
        }
        
        return _instance;
}

void Singleton::destruction()
{
        if (_instance != nullptr) {
                delete _instance;
                _instance = nullptr;
        }
}


