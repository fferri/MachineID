#include "machineid.h"
#include <QtCore>

QString machineID()
{
    QString id("?");
#ifdef _WIN32
#elif __APPLE__
    QStringList args;
    args << "-c" << "ioreg -rd1 -c IOPlatformExpertDevice |  awk '/IOPlatformUUID/ { print $3; }'";
    QProcess proc;
    proc.start("/bin/sh", args);
    proc.waitForFinished();
    id = proc.readAll();
#elif __linux__
    QStringList fs;
    fs << "/var/lib/dbus/machine-id" << "/etc/machine-id";
    for(const QString &f : fs)
    {
        QFile fo(f);
        if(!fo.open(QFile::ReadOnly | QFile::Text)) break;
        QTextStream in(&fo);
        id = in.readAll();
        break;
    }
#endif
    return id;
}

uint32_t machineIDHash()
{
    QString id = machineID();
    QDataStream in(QCryptographicHash::hash(id.toLatin1(), QCryptographicHash::Md5));
    in.setByteOrder(QDataStream::LittleEndian);
    uint32_t result = 0;
    for(int i = 0; i < 4; i++)
    {
        uint32_t x;
        in >> x;
        result ^= x;
    }
    return result;
}
