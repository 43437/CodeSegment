#include <iostream>
#include <string>

using std::string;

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        std::cout<<"c++: Hello "<<argv[1]<<std::endl;
    }
    else
    {
        std::cout<<"c++: Hello world"<<std::endl;
    }

    return 0;
}
