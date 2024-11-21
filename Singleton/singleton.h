// classe Singleton
#ifndef SINGLETON_H
#define SINGLETON_H

class Singleton {
public:
        static Singleton* instance();
        static void destruction();
        
protected:
        Singleton();
        ~Singleton();
        
private:
        static Singleton* _instance;
};

#endif
