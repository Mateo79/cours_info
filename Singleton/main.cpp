#include "singleton.h"

#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, int** argv)
{
        Singleton* s1 = nullptr;
        Singleton* s2 = nullptr;
        //Singleton  s3;
        
        // création 
        s1 = Singleton::instance();
        cout << "s1: " << s1 << "\n";
        s2 = Singleton::instance();
        cout << "s2: " << s2 << "\n";
        
        // destruction
        Singleton::destruction();

        cout << "s1: " << s1 << "\n";
        cout << "s2: " << s2 << "\n";
        s1 = nullptr;
        s2 = nullptr;
        

        return EXIT_SUCCESS;
}
