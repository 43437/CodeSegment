#include "callerprocess.h"

#include <string>

callerprocess::callerprocess(QObject *parent) : QObject(parent)
  ,m_bLineMode(true)
{
    process = new QProcess();  // create on the heap, so it doesn't go out of scope
}

void callerprocess::call()
{
    const QString qstrPath("../build-QtProcessClientDemo-Desktop_Qt_5_12_0_GCC_64bit-Debug/");
    const QString qstrFile("QtProcessClientDemo");
    const QString qsScript("echoBack.sh");
    connect (process, SIGNAL(readyReadStandardOutput()), this, SLOT(processOutput()));  // connect process signals with your code
    connect (process, SIGNAL(readyReadStandardError()), this, SLOT(processOutput()));  // same here
//    process->start(qstrPath + qstrFile);  // start the process
    process->start(qsScript);  // start the process
}

void callerprocess::processOutput()
{
    if (m_bLineMode)                //read line by line
    {
        while(process->canReadLine())
        {
              qDebug() << process->readLine();
         }
    }
    else
    {
        QString strRet = process->readAllStandardOutput();
        qDebug() << "ret: " << strRet;
    }
}

void callerprocess::send(QString qstrMsg)
{
    if (nullptr != this->process)
    {
        std::string strMsg = qstrMsg.toStdString();
        this->process->write(strMsg.data(), strMsg.length());
    }
}

void callerprocess::setLineMode(bool flag)
{
    this->m_bLineMode = flag;
}
