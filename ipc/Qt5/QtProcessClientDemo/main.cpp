#include <QCoreApplication>

#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string line;

    std::cout <<"back: started."<<std::endl;
    while (true)
    {
        std::cin >> line;
        if (!line.compare("break"))
        {
            break;
        }
        std::cout << "back: " << line <<std::endl;
    }
    std::cout <<"back: finished."<<std::endl;
    return a.exec();
}
