#include <QCoreApplication>
#include <iostream>

#include "callerprocess.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    callerprocess cp;
    cp.call();

    cp.send("Hello\n");
    cp.send("Child\n");
    cp.send("Good\n");
    cp.send("break\n");

    return a.exec();
}
