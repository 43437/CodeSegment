#ifndef CALLERPROCESS_H
#define CALLERPROCESS_H

#include <QObject>

#include <QProcess>
#include <QtDebug>

class callerprocess : public QObject
{
    Q_OBJECT
public:
    explicit callerprocess(QObject *parent = nullptr);
    void call();
    void send(QString qstrMsg);
    void setLineMode(bool flag);

signals:

public slots:
    void processOutput();

private:
    QProcess* process;
    bool m_bLineMode;
};

#endif // CALLERPROCESS_H
